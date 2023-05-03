#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <optional>
#include <type_traits>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/query.hpp>

#include "models/lesson_filter/postgre.hpp"
#include "models/lesson_v1/postgre.hpp"
#include "models/lesson_v1/type.hpp"
#include "models/lesson_with_details/postgre.hpp"
#include "models/subgroup/serialize.hpp"
#include "sql_queries.hpp"
#include "utils/convert/drop_properties_ref.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::lesson {

std::vector<models::LessonV1> Controller::Search(
    const std::optional<models::LessonFilter>& filter) const {
    std::optional<models::TupleLessonFilter> filter_tuple =
        convert::DropPropertiesToConstRefs(filter);
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        sql::qGetLessonsByFilter, filter_tuple);
    std::vector<models::LessonV1> lessons;
    lessons.reserve(result.Size());
    auto it = result.begin();
    for (auto& row : result) {
        auto& lesson = lessons.emplace_back();
        auto tuple = convert::DropPropertiesToMutRefs(lesson);
        row.To(tuple, userver::storages::postgres::kRowTag);
    }
    return lessons;
}
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {
}
}  // namespace timetable_vsu_backend::components::controllers::postgres::lesson
