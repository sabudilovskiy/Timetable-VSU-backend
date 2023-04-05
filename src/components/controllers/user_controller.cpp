#include "user_controller.hpp"
#include <fmt/core.h>
#include <boost/uuid/uuid.hpp>
#include <exception>
#include <optional>
#include <userver/storages/postgres/cluster.hpp>
#include "models/user/postgre.hpp"
#include "models/user_type/postgre.hpp"
#include "userver/components/component_context.hpp"
#include "userver/logging/log.hpp"
#include "userver/storages/postgres/cluster_types.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/storages/postgres/query.hpp"
namespace {
const userver::storages::postgres::Query qGetUserByLogin(R"(
    select * from vsu_timetable."user" WHERE login = $1
    )"),
    qAddUser(R"(
    insert into vsu_timetable."user"(login, password, user_type) values ($1, $2, $3) ON CONFLICT DO NOTHING 
    RETURNING id
    )");
}

namespace timetable_vsu_backend::components {
UserController::UserController(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {}

std::optional<models::User> UserController::GetByLogin(
    std::string_view login) const {
  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster, qGetUserByLogin,
      login);
  if (result.IsEmpty()) {
    return std::nullopt;
  }
  return result.AsSingleRow<models::User>(userver::storages::postgres::kRowTag);
}
std::optional<boost::uuids::uuid> UserController::TryToAdd(
    const models::User& user) const {
  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster, qAddUser,
      user.login, user.password, user.user_type);
  if (result.IsEmpty()) {
    return {};
  }
  return result.AsSingleRow<boost::uuids::uuid>();
}
}  // namespace timetable_vsu_backend::components