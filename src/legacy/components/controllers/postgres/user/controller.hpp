#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/models/user/type.hpp"
#include "legacy/models/user_credentials/fwd.hpp"
#include "legacy/models/user_type/type.hpp"

namespace legacy::components::controllers::postgres::user
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;

    static constexpr inline std::string_view kName = "user-controller";

    void InternalForceCreateUser(
        const boost::uuids::uuid&,
        const legacy::models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr);

    utils::SharedTransaction CreateTransaction();

    std::optional<legacy::models::User> GetByToken(
        const boost::uuids::uuid& token,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> CreateRequestTeacher(
        const boost::uuids::uuid& user_id, const std::string& description,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> CreateRequestAdmin(
        const boost::uuids::uuid& user_id, const std::string& description,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<legacy::models::User> GetByCredentials(
        const legacy::models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> TryToAdd(
        const legacy::models::UserCredentials& user_credentials,
        utils::SharedTransaction transaction = nullptr) const;

    static userver::yaml_config::Schema GetStaticConfigSchema();

    utils::SharedTransaction CreateTransaction() const;

    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

    ~Controller();

   protected:
    std::optional<legacy::models::User> HandleUserFromPg(
        userver::storages::postgres::ResultSet& result) const;

   private:
    std::optional<boost::uuids::uuid> root_id;
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace legacy::components::controllers::postgres::user
