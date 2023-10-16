#include "controller.hpp"

#include <fmt/core.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <optional>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/query.hpp>
#include <userver/storages/postgres/result_set.hpp>
#include <userver/yaml_config/merge_schemas.hpp>
#include <userver/yaml_config/schema.hpp>
#include <utils/convert/drop_properties_ref.hpp>
#include <utils/postgres_helper.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/components/controllers/postgres/user/sql_queries.hpp"
#include "config_schema.hpp"
#include "legacy/models/user/postgre.hpp"
#include "legacy/models/user/type.hpp"
#include "legacy/models/user_credentials/postgre.hpp"

namespace legacy::components::controllers::postgres::user
{
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster())
{
    legacy::models::UserCredentials root;
    root.login() = config["root"]["login"].As<std::string>();
    root.password() = config["root"]["password"].As<std::string>();
    root_id = boost::lexical_cast<boost::uuids::uuid>(
        config["root"]["id"].As<std::string>());
    try
    {
        InternalForceCreateUser(root_id.value(), root);
    }
    catch (std::exception& exc)
    {
        LOG_WARNING() << fmt::format("Error while creating superuser : {}",
                                     exc.what());
        root_id = std::nullopt;
    }
}

utils::SharedTransaction Controller::CreateTransaction()
{
    return utils::MakeSharedTransaction(pg_cluster_);
}

void Controller::InternalForceCreateUser(
    const boost::uuids::uuid&, const legacy::models::UserCredentials& user_credentials,
    utils::SharedTransaction transaction)
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    utils::PgExecute(transaction, sql::qDropUserById, root_id);
    utils::PgExecute(transaction, sql::qDropUserByLogin,
                     user_credentials.login());
    utils::PgExecute(transaction, sql::qInternalAddUser, root_id,
                     user_credentials);
}

std::optional<boost::uuids::uuid> Controller::CreateRequestTeacher(
    const boost::uuids::uuid& user_id, const std::string& description,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result = utils::PgExecute(transaction, sql::qCreateTeacherRequest,
                                      user_id, description);
    return utils::ConvertPgResultToOptionalItem<boost::uuids::uuid>(pg_result);
}

std::optional<boost::uuids::uuid> Controller::CreateRequestAdmin(
    const boost::uuids::uuid& user_id, const std::string& description,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result = utils::PgExecute(transaction, sql::qCreateAdminRequest,
                                      user_id, description);
    return utils::ConvertPgResultToOptionalItem<boost::uuids::uuid>(pg_result);
}

std::optional<legacy::models::User> Controller::HandleUserFromPg(
    userver::storages::postgres::ResultSet& result) const
{
    if (result.IsEmpty())
    {
        return std::nullopt;
    }
    std::optional<legacy::models::User> user = std::nullopt;
    if (result.Size() == 1)
    {
        user = utils::ConvertPgResultToItem<legacy::models::User>(result);
    }
    else if (result.Size() != 0)
    {
        LOG_WARNING() << fmt::format("Unexpected quantity from postgres: {}",
                                     result.Size());
    }
    if (user && user->id() == root_id)
    {
        user->type() = legacy::models::UserType::kRoot;
    }
    return user;
}

std::optional<legacy::models::User> Controller::GetByCredentials(
    const legacy::models::UserCredentials& user_credentials,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto result = transaction->transaction_.Execute(
        sql::qGetUserByCredentials,
        utils::convert::DropPropertiesToConstRefs(user_credentials));
    return HandleUserFromPg(result);
}

std::optional<legacy::models::User> Controller::GetByToken(
    const boost::uuids::uuid& token, utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto result =
        transaction->transaction_.Execute(sql::qGetUserByToken, token);
    return HandleUserFromPg(result);
}

utils::SharedTransaction Controller::CreateTransaction() const
{
    return utils::MakeSharedTransaction(pg_cluster_);
}

std::optional<boost::uuids::uuid> Controller::TryToAdd(
    const legacy::models::UserCredentials& user_credentials,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto result =
        utils::PgExecute(transaction, sql::qAddUser, user_credentials);
    if (result.IsEmpty())
    {
        return {};
    }
    return result.AsSingleRow<boost::uuids::uuid>();
}

Controller::~Controller()
{
    pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                         sql::qDropUserById, root_id);
}

userver::yaml_config::Schema Controller::GetStaticConfigSchema()
{
    return userver::yaml_config::MergeSchemas<
        userver::components::LoggableComponentBase>(config::schema);
}
}  // namespace legacy::components::controllers::postgres::user
