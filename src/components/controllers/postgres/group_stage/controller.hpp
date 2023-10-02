#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <utils/shared_transaction.hpp>
#include <vector>

#include "models/group_stage/type.hpp"
#include "models/group_stage_filter/type.hpp"
#include "models/request_privileges/type.hpp"
#include "models/teacher/type.hpp"
#include "models/teacher_filter/type.hpp"
#include "models/teacher_info/type.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::group_stage
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "group_stage_controller";

    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

    std::vector<models::GroupStage> GetByFilter(
        const std::optional<models::GroupStageFilter>& filter,
        utils::SharedTransaction transaction = nullptr) const;

   public:
    timetable_vsu_backend::utils::SharedTransaction CreateTransaction();

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace
   // timetable_vsu_backend::components::controllers::postgres::group_stage
