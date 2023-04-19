#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <vector>

#include "models/lesson_filter/fwd.hpp"
#include "models/lesson_with_details/type.hpp"

namespace timetable_vsu_backend::components::controllers::postgres {
class LessonDetailsController final
    : public userver::components::LoggableComponentBase {
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName =
        "lesson_details_controller";
    std::vector<models::LessonWithDetails> Search(
        const std::optional<models::LessonFilter>& filter) const;

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace timetable_vsu_backend::components::controllers::postgres