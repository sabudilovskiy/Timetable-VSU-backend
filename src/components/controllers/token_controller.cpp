#include "token_controller.hpp"
#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <optional>
#include <userver/storages/postgres/cluster.hpp>
#include "userver/components/component_context.hpp"
#include "userver/storages/postgres/cluster_types.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/storages/postgres/query.hpp"
#include "userver/utils/datetime.hpp"
#include "../../models/user/postgre.hpp"
#include "../../models/user_type/postgre.hpp"

namespace {
const userver::storages::postgres::Query qGetUserByTokenId(R"(
   WITH found_token AS (select user_id
                 from vsu_timetable.token WHERE id = $1 AND expire_time > $2)
   SELECT id, login, password, user_type from vsu_timetable."user" LEFT OUTER JOIN found_token ON user_id = "user".id
    )"),
    qAddToken(R"(
      insert into vsu_timetable."token" (user_id, expire_time) values ($1, $2) RETURNING id
    )");
}

namespace timetable_vsu_backend::components {
TokenController::TokenController(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {}
std::optional<models::User> TokenController::GetById(
    std::string_view id) const {
  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster, qGetUserByTokenId, id, userver::utils::datetime::Now());
  if (result.IsEmpty()) {
    return std::nullopt;
  }
  return result.AsSingleRow<models::User>();
}

boost::uuids::uuid TokenController::CreateNew(const models::User::Id& id, const std::chrono::system_clock::time_point& time) const {
  auto result = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, qAddToken, id, time);
  return result.AsSingleRow<boost::uuids::uuid>();
}
}  // namespace timetable_vsu_backend::components