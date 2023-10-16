#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/models/user/type.hpp"

namespace legacy::components::controllers::postgres::token
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;

    static constexpr inline std::string_view kName = "token_controller";

    std::optional<legacy::models::User> GetById(
        std::string_view id,
        utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> CreateNew(
        const boost::uuids::uuid& user_id,
        const std::chrono::system_clock::time_point& time,
        utils::SharedTransaction transaction = nullptr) const;

    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace legacy::components::controllers::postgres::token
