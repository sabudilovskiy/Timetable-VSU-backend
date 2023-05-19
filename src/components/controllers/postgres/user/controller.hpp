#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>

#include "models/user/type.hpp"
#include "models/user_credentials/fwd.hpp"
#include "models/user_type/type.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::user
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;

    static constexpr inline std::string_view kName = "user-controller";

    void InternalForceCreateUser(
        const boost::uuids::uuid&,
        const models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr);

    utils::SharedTransaction CreateTransaction();

    std::optional<models::User> GetByToken(
        const boost::uuids::uuid& token,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> CreateRequestTeacher(
        const boost::uuids::uuid& user_id, const std::string& description,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> CreateRequestAdmin(
        const boost::uuids::uuid& user_id, const std::string& description,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<models::User> GetByCredentials(
        const models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> TryToAdd(
        const models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr) const;

    static userver::yaml_config::Schema GetStaticConfigSchema();

    utils::SharedTransaction CreateTransaction() const;

    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

    ~Controller();

   protected:
    std::optional<models::User> HandleUserFromPg(
        userver::storages::postgres::ResultSet& result) const;

   private:
    std::optional<boost::uuids::uuid> root_id;
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace timetable_vsu_backend::components::controllers::postgres::user
