#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <openapi/json/serialize/enum.hpp>
#include <optional>
#include <type_traits>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/query.hpp>
#include <utils/convert/drop_properties_ref.hpp>
#include <utils/postgres_helper.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/models/admin_account/postgre.hpp"
#include "legacy/models/admin_account/type.hpp"
#include "legacy/models/admin_filter/postgre.hpp"
#include "legacy/models/user_credentials/postgre.hpp"
#include "sql_queries.hpp"

namespace legacy::components::controllers::postgres::admin
{
utils::SharedTransaction Controller::CreateTransaction() const
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

std::optional<legacy::models::AdminAccount> Controller::GetAccountByAdminId(
    const boost::uuids::uuid& admin_id,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result = transaction->transaction_.Execute(
        sql::qGetAdminAccountByAdminId, admin_id);
    return utils::ConvertPgResultToOptionalItem<legacy::models::AdminAccount>(
        pg_result);
}

std::optional<legacy::models::AdminAccount> Controller::CreateAdmin(
    const legacy::models::UserCredentials& user,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction, pg_cluster_);
    auto tuple_user = utils::convert::DropPropertiesToConstRefs(user);
    auto result_id =
        transaction->transaction_.Execute(sql::qCreateAdminAccount, tuple_user);
    if (result_id.Size() != 1)
    {
        return std::nullopt;
    }
    boost::uuids::uuid admin_id = result_id.AsSingleRow<boost::uuids::uuid>();
    return GetAccountByAdminId(admin_id, transaction);
}

std::vector<legacy::models::AdminAccount> Controller::GetByFilter(
    std::optional<legacy::models::AdminFilter>& filter,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qGetAdminsByFilter, filter);
    return utils::ConvertPgResultToArray<legacy::models::AdminAccount>(
        pg_result);
}

}  // namespace legacy::components::controllers::postgres::admin
