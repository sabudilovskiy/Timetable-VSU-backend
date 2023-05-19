#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <vector>

#include "models/admin_account/type.hpp"
#include "models/admin_filter/type.hpp"
#include "models/user_credentials/type.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::admin
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "admin_controller";
    std::optional<models::AdminAccount> GetAccountByAdminId(
        const boost::uuids::uuid& admin_id,
        utils::SharedTransaction transaction = nullptr) const;
    std::optional<models::AdminAccount> CreateAdmin(
        const models::UserCredentials& user,
        utils::SharedTransaction transaction = nullptr) const;
    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);
    std::vector<models::AdminAccount> GetByFilter(
        std::optional<models::AdminFilter>& filter,
        utils::SharedTransaction transaction = nullptr) const;
    utils::SharedTransaction CreateTransaction() const;

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace timetable_vsu_backend::components::controllers::postgres::admin
