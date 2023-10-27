#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <openapi/json/serialize/enum.hpp>
#include <optional>
#include <type_traits>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/exceptions.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/io/type_traits.hpp>
#include <userver/storages/postgres/query.hpp>
#include <utils/convert/drop_properties_ref.hpp>
#include <utils/postgres_helper.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/models/admin_account/postgre.hpp"
#include "legacy/models/admin_filter/postgre.hpp"
#include "legacy/models/request_privileges/type.hpp"
#include "legacy/models/substring/postgre.hpp"
#include "legacy/models/teacher/postgre.hpp"
#include "legacy/models/teacher_filter/postgre.hpp"
#include "legacy/models/teacher_info/postgre.hpp"
#include "legacy/models/user_credentials/postgre.hpp"
#include "sql_queries.hpp"
#include "legacy/models/substring/postgre.hpp"

namespace legacy::components::controllers::postgres::teacher
{
::utils::SharedTransaction Controller::CreateTransaction()
{
    return ::utils::MakeSharedTransaction(pg_cluster_);
}
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster())
{
}
std::vector<legacy::models::Teacher> Controller::GetByFilter(
    std::optional<legacy::models::TeacherFilter>& filter,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qGetTeachersByFilter, filter);
    return utils::ConvertPgResultToArray<legacy::models::Teacher>(pg_result);
}

std::optional<boost::uuids::uuid> Controller::CreateTeacher(
    const legacy::models::TeacherInfo& teacher_info,
    ::utils::SharedTransaction transaction) const
{
    try
    {
        utils::FillSharedTransaction(transaction, pg_cluster_);
        auto pg_result =
            utils::PgExecute(transaction, sql::qCreateTeacher, teacher_info);
        return utils::ConvertPgResultToItem<boost::uuids::uuid>(pg_result);
    }
    catch (std::exception& exc)
    {
        LOG_INFO() << fmt::format("Department id : {} not found",
                                  to_string(teacher_info.department_id()));
        return std::nullopt;
    }
}

std::optional<boost::uuids::uuid> Controller::ApproveAndLink(
    const boost::uuids::uuid& request_id, const boost::uuids::uuid& teacher_id,
    ::utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto id_user = utils::ConvertPgResultToOptionalItem<boost::uuids::uuid>(
        utils::PgExecute(transaction, sql::qGetUserIdFromRequest, request_id));
    if (!id_user)
    {
        return std::nullopt;
    }
    auto linked = Link(*id_user, teacher_id, transaction);
    if (linked)
    {
        utils::PgExecute(transaction, sql::qDropRequestById, request_id);
    }
    return linked;
}

std::optional<boost::uuids::uuid> Controller::Link(
    const boost::uuids::uuid& user_id, const boost::uuids::uuid& teacher_id,
    ::utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto created = utils::PgSafeExecute(transaction, sql::qCreateLink, user_id,
                                        teacher_id);
    return utils::ConvertPgResultToOptionalItem<boost::uuids::uuid>(created);
}

std::optional<boost::uuids::uuid> Controller::ApproveAndCreateAccount(
    const boost::uuids::uuid& request_id,
    const legacy::models::TeacherInfo& teacher_info,
    ::utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto id_user_result =
        utils::PgExecute(transaction, sql::qGetUserIdFromRequest, request_id);
    auto id_user = utils::ConvertPgResultToOptionalItem<boost::uuids::uuid>(
        id_user_result);
    if (!id_user)
    {
        return std::nullopt;
    }
    auto create_teacher_result =
        utils::PgSafeExecute(transaction, sql::qCreateTeacher, teacher_info);
    if (!create_teacher_result)
    {
        return std::nullopt;
    }
    auto created_teacher_id = utils::ConvertPgResultToItem<boost::uuids::uuid>(
        create_teacher_result.value());
    utils::PgExecute(transaction, sql::qDropRequestById, request_id);
    return Link(id_user.value(), created_teacher_id, transaction);
}

std::vector<legacy::models::RequestPrivileges> Controller::GetAllRequests(
    ::utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result = utils::PgExecute(transaction, sql::qGetAllRequests);
    return utils::ConvertPgResultToArray<legacy::models::RequestPrivileges>(
        pg_result);
}

std::optional<boost::uuids::uuid> Controller::DropRequest(
    const boost::uuids::uuid& request_id,
    ::utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qDropRequestById, request_id);
    return utils::ConvertPgResultToOptionalItem<boost::uuids::uuid>(pg_result);
}

}  // namespace legacy::components::controllers::postgres::teacher
   // ::components::controllers::postgres::teacher
