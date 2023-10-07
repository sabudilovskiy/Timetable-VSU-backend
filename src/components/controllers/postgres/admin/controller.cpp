#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
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

#include "models/admin_account/postgre.hpp"
#include "models/admin_account/type.hpp"
#include "models/admin_filter/postgre.hpp"
#include "models/subgroup/serialize.hpp"
#include "models/user_credentials/postgre.hpp"
#include "sql_queries.hpp"

namespace components::controllers::postgres::admin
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

std::optional<models::AdminAccount> Controller::GetAccountByAdminId(
    const boost::uuids::uuid& admin_id,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction,
                                                        pg_cluster_);
    auto pg_result = transaction->transaction_.Execute(
        sql::qGetAdminAccountByAdminId, admin_id);
    return utils::ConvertPgResultToOptionalItem<models::AdminAccount>(
        pg_result);
}

std::optional<models::AdminAccount> Controller::CreateAdmin(
    const models::UserCredentials& user,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction,
                                                        pg_cluster_);
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

std::vector<models::AdminAccount> Controller::GetByFilter(
    std::optional<models::AdminFilter>& filter,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction,
                                                        pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qGetAdminsByFilter, filter);
    return utils::ConvertPgResultToArray<models::AdminAccount>(pg_result);
}

}  // namespace components::controllers::postgres::admin
