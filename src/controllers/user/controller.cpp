#include "controller.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
#include <codegen/sql.hpp>
#include <openapi/postgres/mapping.hpp>
#include <optional>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/io/optional.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/io/string_types.hpp>
#include <userver/storages/postgres/io/uuid.hpp>
#include <userver/utils/datetime.hpp>
#include <userver/yaml_config/merge_schemas.hpp>
#include <utils/shared_transaction.hpp>

#include "controller_fwd.hpp"
#include "legacy/models/user_type/postgre.hpp"
#include "legacy/models/user_type/type.hpp"
#include "models/user/postgres.hpp"
#include "models/user_credentials/postgres.hpp"

namespace controllers::user
{
namespace
{
boost::uuids::uuid GetRootId(const userver::components::ComponentConfig& cfg)
{
    return boost::lexical_cast<boost::uuids::uuid>(
        cfg["root"]["id"].As<std::string>());
}
models::UserCredentials GetRootCreds(
    const userver::components::ComponentConfig& cfg)
{
    return models::UserCredentials{
        .login = {cfg["root"]["login"].As<std::string>()},
        .password = {cfg["root"]["password"].As<std::string>()}};
}
}  // namespace
const std::string schema =
    R"(
type: object
description: Компонент, отвечающий за авторизацию и определение типа пользователей
additionalProperties: false
properties:
    root:
        type: object
        description: Настройки суперпользователя. Он будет создан на время работы сервиса, а затем будет удален из БД. Логин и id будут освобождены для него.
        additionalProperties: false
        properties:
            login:
                type: string
                description: Логин для суперпользователя
            password:
                type: string
                description: Пароль для суперпользователя
            id: 
                type: string
                description: UUID суперпользователя 
)";

void Controller::InternalForceCreateUser(
    const boost::uuids::uuid& user_id,
    const models::UserCredentials& user_credentials,
    utils::SharedTransaction tr) const
{
    FillTransaction(tr);
    tr->Execute(sql::drop_user_by_id, user_id);
    tr->Execute(sql::drop_user_by_login, user_credentials.login);
    tr->Execute(sql::internal_add_user, user_id, user_credentials);
}

std::optional<models::User> Controller::HandleUserFromPg(
    const userver::storages::postgres::ResultSet& result) const
{
    if (result.IsEmpty())
    {
        return std::nullopt;
    }
    auto user =
        result.AsSingleRow<models::User>(userver::storages::postgres::kRowTag);
    if (user.id == root_id)
    {
        user.type() = legacy::models::UserType::kRoot;
    }
    return user;
}

std::optional<models::User> Controller::GetByCredentials(
    const models::UserCredentials& user_credentials,
    utils::SharedTransaction tr) const
{
    FillTransaction(tr);
    return HandleUserFromPg(
        tr->Execute(sql::get_user_by_credentials, user_credentials));
}

std::optional<boost::uuids::uuid> Controller::TryToAdd(
    const models::UserCredentials& user_credentials,
    utils::SharedTransaction tr) const
{
    FillTransaction(tr);
    return tr->Execute_R<std::optional<boost::uuids::uuid>>(sql::add_user,
                                                            user_credentials);
}
std::optional<models::User> Controller::GetByToken(
    const boost::uuids::uuid& token, utils::SharedTransaction tr) const
{
    FillTransaction(tr);
    return tr->Execute_R<std::optional<models::User>>(sql::get_user_by_token,
                                                      token);
}

userver::yaml_config::Schema Controller::GetStaticConfigSchema()
{
    return userver::yaml_config::MergeSchemas<
        userver::components::LoggableComponentBase>(schema);
}

void Append(userver::components::ComponentList& list)
{
    list.Append<Controller>();
}
Controller::Controller(const userver::components::ComponentConfig& cfg,
                       const userver::components::ComponentContext& ctx)
    : Base(cfg, ctx), root_id(GetRootId(cfg)), root_creds(GetRootCreds(cfg))
{
}

namespace
{
const userver::storages::postgres::Query* GetRequestRihtsType(
    legacy::models::UserType user_type)
{
    switch (user_type)
    {
        case legacy::models::UserType::kUser:
            return nullptr;
        case legacy::models::UserType::kAdmin:
            return &sql::create_admin_request;
        case legacy::models::UserType::kRoot:
            return nullptr;
        case legacy::models::UserType::kTeacher:
            return &sql::create_teacher_request;
    }
}
}  // namespace

std::optional<boost::uuids::uuid> Controller::CreateRequestRights(
    const boost::uuids::uuid& user_id, const std::string& description,
    legacy::models::UserType user_type,
    utils::SharedTransaction transaction) const
{
    FillTransaction(transaction);
    auto query = GetRequestRihtsType(user_type);
    if (query)
    {
        return transaction->Execute_R<std::optional<boost::uuids::uuid>>(
            *query, user_id, description);
    }
    else
    {
        return std::nullopt;
    }
}

void Controller::OnAllComponentsLoaded()
{
    InternalForceCreateUser(root_id, root_creds);
}

}  // namespace controllers::user
