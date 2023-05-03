#include "controller.hpp"

#include <fmt/core.h>

#include <boost/uuid/uuid.hpp>
#include <exception>
#include <optional>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/query.hpp>

#include "components/controllers/postgres/user/sql_queries.hpp"
#include "config_schema.hpp"
#include "models/user/postgre.hpp"
#include "models/user/type.hpp"
#include "models/user_credentials/postgre.hpp"
#include "userver/components/component_config.hpp"
#include "userver/yaml_config/merge_schemas.hpp"
#include "userver/yaml_config/schema.hpp"
#include "utils/convert/drop_properties_ref.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::user {
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {
    models::UserCredentials root;
    root.login() = config["root_login"].As<std::string>();
    root.password() = config["root_password"].As<std::string>();
    root_id = TryToAdd(root);
    if (!root_id) {
        LOG_WARNING() << fmt::format("Create superuser was failed");
    } else {
        LOG_DEBUG() << fmt::format("Created superuser with login: {}",
                                   root.login());
    }
}

std::optional<models::User> Controller::GetByCredentials(
    const models::UserCredentials& user_credentials) const {
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster, sql::qGetUser,
        utils::convert::DropPropertiesToConstRefs(user_credentials));
    if (result.IsEmpty()) {
        return std::nullopt;
    }
    std::optional<models::User> user = std::nullopt;
    if (result.Size() == 1) {
        models::User read;
        auto pg_user = utils::convert::DropPropertiesToMutRefs(read);
        result[0].To(pg_user, userver::storages::postgres::kRowTag);
        user = read;
    } else if (result.Size() != 0) {
        LOG_WARNING() << fmt::format("Unexpected quantity from postgres: {}",
                                     result.Size());
    }
    if (user && root_id && user->id() == root_id) {
        user->type() = models::UserType::kRoot;
    }
    return user;
}
std::optional<boost::uuids::uuid> Controller::TryToAdd(
    const models::UserCredentials& user_credentials) const {
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster, sql::qAddUser,
        utils::convert::DropPropertiesToConstRefs(user_credentials));
    if (result.IsEmpty()) {
        return {};
    }
    return result.AsSingleRow<boost::uuids::uuid>();
}
Controller::~Controller() {
    pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                         sql::qDropUserById, root_id);
}

userver::yaml_config::Schema Controller::GetStaticConfigSchema() {
    return userver::yaml_config::MergeSchemas<
        userver::components::LoggableComponentBase>(config::schema);
}
}  // namespace timetable_vsu_backend::components::controllers::postgres::user