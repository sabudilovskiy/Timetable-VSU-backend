#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <utils/shared_transaction.hpp>
#include <vector>

#include "legacy/models/admin_account/type.hpp"
#include "legacy/models/admin_filter/type.hpp"
#include "legacy/models/user_credentials/type.hpp"

namespace legacy::components::controllers::postgres::admin
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "admin_controller";
    std::optional<legacy::models::AdminAccount> GetAccountByAdminId(
        const boost::uuids::uuid& admin_id,
        utils::SharedTransaction transaction = nullptr) const;
    std::optional<legacy::models::AdminAccount> CreateAdmin(
        const legacy::models::UserCredentials& user,
        utils::SharedTransaction transaction = nullptr) const;
    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);
    std::vector<legacy::models::AdminAccount> GetByFilter(
        std::optional<legacy::models::AdminFilter>& filter,
        utils::SharedTransaction transaction = nullptr) const;
    utils::SharedTransaction CreateTransaction() const;

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace legacy::components::controllers::postgres::admin
