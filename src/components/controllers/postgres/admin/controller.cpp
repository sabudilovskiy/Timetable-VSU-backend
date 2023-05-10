#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

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

#include "models/admin_account/postgre.hpp"
#include "models/subgroup/serialize.hpp"
#include "models/user_credentials/postgre.hpp"
#include "sql_queries.hpp"
#include "utils/convert/drop_properties_ref.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::admin {
vsu_timetable::utils::SharedTransaction Controller::CreateTransaction() {
    return vsu_timetable::utils::MakeSharedTransaction(pg_cluster_);
}
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {
}

std::optional<models::AdminAccount> Controller::GetAccountByAdminId(
    const boost::uuids::uuid& admin_id,
    vsu_timetable::utils::SharedTransaction transaction) const {
    vsu_timetable::utils::FillSharedTransaction(transaction, pg_cluster_);
    auto result = transaction->transaction_.Execute(
        sql::qGetAdminAccountByAdminId, admin_id);
    models::AdminAccount account;
    models::AdminAccountTuple tuple_account =
        utils::convert::DropPropertiesToMutRefs(account);
    result[0].To(tuple_account, userver::storages::postgres::kRowTag);
    return account;
}

std::optional<models::AdminAccount> Controller::CreateAdmin(
    const models::UserCredentials& user,
    vsu_timetable::utils::SharedTransaction transaction) const {
    vsu_timetable::utils::FillSharedTransaction(transaction, pg_cluster_);
    auto tuple_user = utils::convert::DropPropertiesToConstRefs(user);
    auto result_id =
        transaction->transaction_.Execute(sql::qCreateAdminAccount, tuple_user);
    if (result_id.Size() != 1) {
        return std::nullopt;
    }
    boost::uuids::uuid admin_id = result_id.AsSingleRow<boost::uuids::uuid>();
    return GetAccountByAdminId(admin_id, transaction);
}
}  // namespace timetable_vsu_backend::components::controllers::postgres::admin
