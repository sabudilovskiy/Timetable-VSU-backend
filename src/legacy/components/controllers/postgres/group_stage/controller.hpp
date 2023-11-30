#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <utils/shared_transaction.hpp>
#include <vector>

#include "legacy/models/group_stage/type.hpp"
#include "legacy/models/group_stage_filter/type.hpp"
#include "legacy/models/request_privileges/type.hpp"
#include "legacy/models/teacher/type.hpp"
#include "legacy/models/teacher_filter/type.hpp"
#include "legacy/models/teacher_info/type.hpp"

namespace legacy::components::controllers::postgres::group_stage
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "group_stage_controller";

    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

    std::vector<legacy::models::GroupStage> GetByFilter(
        const std::optional<legacy::models::GroupStageFilter>& filter,
        utils::SharedTransaction transaction = nullptr) const;

   public:
    ::utils::SharedTransaction CreateTransaction();

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace legacy::components::controllers::postgres::group_stage
   // ::components::controllers::postgres::group_stage
