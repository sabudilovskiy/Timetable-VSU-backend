#pragma once

#include <boost/uuid/uuid.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <utils/component_list_fwd.hpp>
#include <utils/pg_controller.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/models/user_type/type.hpp"
#include "models/user/type.hpp"
#include "models/user_credentials/type.hpp"

namespace controllers::user
{
using Base = utils::PgController<"new-user-controller", "postgres-db-1">;
struct Controller : Base
{
    Controller(const userver::components::ComponentConfig& cfg,
               const userver::components::ComponentContext& ctx);

    void InternalForceCreateUser(
        const boost::uuids::uuid&,
        const models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<models::User> GetByCredentials(
        const models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> TryToAdd(
        const models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr) const;
    std::optional<models::User> GetByToken(
        const boost::uuids::uuid& token,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> CreateRequestRights(
        const boost::uuids::uuid& user_id, const std::string& description,
        legacy::models::UserType user_type,
        utils::SharedTransaction transaction = nullptr) const;

    static userver::yaml_config::Schema GetStaticConfigSchema();
    void OnAllComponentsLoaded();

   protected:
    std::optional<models::User> HandleUserFromPg(
        const userver::storages::postgres::ResultSet& result) const;
    const boost::uuids::uuid root_id;
    const models::UserCredentials root_creds;
};
}  // namespace controllers::user
