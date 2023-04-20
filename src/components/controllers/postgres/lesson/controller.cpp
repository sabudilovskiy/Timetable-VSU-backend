#include "controller.hpp"

#include <fmt/core.h>

#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/query.hpp>

#include "models/lesson_filter/type.hpp"
#include "models/lesson_with_details/postgre.hpp"
#include "models/lesson_with_details/type.hpp"
namespace timetable_vsu_backend::components::controllers::postgres {
namespace {
const userver::storages::postgres::Query qGetLessonsByFilter(R"(
    WITH lesson_info as (SELECT
        l.id AS lesson_id,
        l.begin AS lesson_begin,
        l.end AS lesson_end,
        l.number_lesson AS lesson_number,
        l.type_lesson AS lesson_type,
        l.type_week AS lesson_week_type,
        l.subgroup AS lesson_subgroup,
        l.day AS lesson_day,
        r.id AS room_id,
        r.name AS room_name,
        s.id AS subject_id,
        s.name AS subject_name,
        gs.id AS group_stage_id,
        gs.begin AS group_stage_begin,
        gs.end AS group_stage_end,
        gs.course AS group_stage_course,
        g.id AS group_id,
        g.name AS group_name,
        g.type AS group_type,
        f.id AS faculty_id,
        f.name AS faculty_name,
        d.id AS department_id,
        d.name AS department_name,
        t.id AS teacher_id,
        t.fio AS teacher_fio,
        t.bio AS teacher_bio
    FROM vsu_timetable.lesson AS l
        LEFT JOIN vsu_timetable.room AS r ON l.id_room = r.id
        LEFT JOIN vsu_timetable.shedule AS sh ON l.id_shedule = sh.id
        LEFT JOIN vsu_timetable.subject AS s ON sh.id_subject = s.id
        LEFT JOIN vsu_timetable.group_stage AS gs ON sh.id_group_stage = gs.id
        LEFT JOIN vsu_timetable.group AS g ON gs.id_group = g.id
        LEFT JOIN vsu_timetable.teacher AS t ON sh.id_teacher = t.id
        LEFT JOIN vsu_timetable.department AS d ON t.id_department = d.id
        LEFT JOIN vsu_timetable.faculty AS f ON d.id_faculty = f.id
    )
    SELECT 
        lesson_id,
        lesson_begin,
        lesson_end,
        lesson_number,
        lesson_type,
        lesson_week_type,
        lesson_subgroup,
        lesson_day,
        room_id,
        room_name,
        subject_id,
        subject_name,
        group_id,
        group_stage_course,
        group_name,
        group_type,
        faculty_id,
        faculty_name,
        department_id,
        department_name,
        teacher_id,
        teacher_fio,
        teacher_bio
    FROM lesson_info
    ;
    )");
}
// filter временно не используется
std::vector<models::LessonWithDetails> LessonDetailsController::Search(
    const std::optional<models::LessonFilter>& filter) const {
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        qGetLessonsByFilter);
    std::vector<models::LessonWithDetails> lessons;
    lessons.reserve(result.Size());
    for (auto& row : result) {
        lessons.emplace_back(row.As<models::LessonWithDetails>(
            userver::storages::postgres::kRowTag));
    }
    return lessons;
}
LessonDetailsController::LessonDetailsController(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {
}
}  // namespace timetable_vsu_backend::components::controllers::postgres