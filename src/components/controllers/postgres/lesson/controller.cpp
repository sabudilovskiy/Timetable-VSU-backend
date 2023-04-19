#include "controller.hpp"

#include <fmt/core.h>

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/query.hpp>

#include "models/lesson_with_details/postgre.hpp"
#include "userver/logging/log.hpp"
namespace timetable_vsu_backend::components::controllers::postgres {
namespace {
const userver::storages::postgres::Query qGetLessonsByFilter(R"(
    SELECT
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
        LEFT JOIN vsu_timetable.faculty AS f ON d.id_faculty = f.id;
    )");
}
// filter временно не используется
std::vector<models::LessonWithDetails> LessonDetailsController::Search(
    const std::optional<models::LessonFilter>& /*filter*/) const {
    LOG_DEBUG() << "start execute";
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        qGetLessonsByFilter);
    LOG_DEBUG() << "end execute";
    auto lessons = result.AsContainer<std::vector<models::LessonWithDetails>>();
    LOG_DEBUG() << "end parse to container";
    return lessons;
}
}  // namespace timetable_vsu_backend::components::controllers::postgres