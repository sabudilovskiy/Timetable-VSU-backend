#pragma once
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>

#include "models/user/type.hpp"

namespace timetable_vsu_backend::components::controllers::postgres {

class UserController final : public userver::components::LoggableComponentBase {
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "user_controller";
    std::optional<models::User> GetByLogin(std::string_view login) const;
    std::optional<boost::uuids::uuid> TryToAdd(const models::User& user) const;
    UserController(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context);

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace timetable_vsu_backend::components::controllers::postgres