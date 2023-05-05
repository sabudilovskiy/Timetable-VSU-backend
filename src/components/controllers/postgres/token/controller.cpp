#include "controller.hpp"

#include <fmt/core.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
#include <optional>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/query.hpp>
#include <userver/utils/datetime.hpp>

#include "models/user/postgre.hpp"
#include "models/user_type/postgre.hpp"
#include "sql_queries.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::token {
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {
}
std::optional<models::User> Controller::GetById(std::string_view id) const {
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::qGetUserByTokenId, id, userver::utils::datetime::Now());
    if (result.IsEmpty()) {
        return std::nullopt;
    }
    return result.AsSingleRow<models::User>(
        userver::storages::postgres::kRowTag);
}

std::optional<boost::uuids::uuid> Controller::CreateNew(
    const boost::uuids::uuid& user_id,
    const std::chrono::system_clock::time_point& time) const {
    LOG_DEBUG() << fmt::format("Try to create new token, id_user: {}",
                               boost::uuids::to_string(user_id));
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster, sql::qAddToken,
        user_id, time);
    if (result.IsEmpty()) {
        return {};
    }
    return result.AsSingleRow<boost::uuids::uuid>();
}
}  // namespace timetable_vsu_backend::components::controllers::postgres::token
