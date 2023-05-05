#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>

#include "models/user/type.hpp"
#include "models/user_credentials/fwd.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::user {

class Controller final : public userver::components::LoggableComponentBase {
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "user-controller";
    std::optional<models::User> GetByCredentials(
        const models::UserCredentials& user_credentials) const;
    std::optional<boost::uuids::uuid> TryToAdd(
        const models::UserCredentials& user_credentials) const;
    static userver::yaml_config::Schema GetStaticConfigSchema();
    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);
    ~Controller();

   protected:
    boost::uuids::uuid root_id;
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace timetable_vsu_backend::components::controllers::postgres::user
