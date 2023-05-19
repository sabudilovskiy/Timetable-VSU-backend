#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <vector>

#include "models/teacher/type.hpp"
#include "models/teacher_filter/type.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::teacher {
class Controller final : public userver::components::LoggableComponentBase {
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "teacher_controller";
    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);
    std::vector<models::Teacher> GetByFilter(
        std::optional<models::TeacherFilter>& filter,
        vsu_timetable::utils::SharedTransaction transaction = nullptr) const;
    vsu_timetable::utils::SharedTransaction CreateTransaction();

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace
   // timetable_vsu_backend::components::controllers::postgres::teacher
