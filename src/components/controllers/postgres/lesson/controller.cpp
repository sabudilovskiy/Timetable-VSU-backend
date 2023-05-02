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
#include "utils/convert/drop_properties_ref.hpp"

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
        group_stage_id AS group_id,
        group_stage_course AS group_course,
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
    WHERE 
    ($1.lesson_ids IS null OR lesson_id = ANY($1.lesson_ids)) and
    ($1.begin IS null OR $1.begin <= lesson_end) and
    ($1."end" IS null OR $1."end" >= lesson_begin) and
    ($1.days IS null OR lesson_day = ANY($1.days)) and
	($1.department_ids IS null OR department_id = ANY($1.department_ids)) and
	($1.department_names IS null OR department_name = ANY($1.department_names)) and
	($1.faculty_ids IS null OR faculty_id = ANY($1.faculty_ids)) and
	($1.faculty_names IS null OR faculty_name = ANY($1.faculty_names)) and
	($1.group_ids IS null OR group_stage_id = ANY($1.group_ids)) and
	($1.group_names IS null OR group_name = ANY($1.group_names)) and
    ($1.group_courses is null OR group_stage_course = ANY($1.group_courses)) and
    ($1.group_types is null OR group_type = ANY($1.group_types)) and
    ($1.room_ids IS null OR room_id = ANY($1.room_ids)) and
	($1.room_names IS null OR room_name = ANY($1.room_names)) and
	($1.subject_names IS null OR subject_name = ANY($1.subject_names)) and
    ($1.subject_ids IS null OR subject_id = ANY($1.subject_ids)) and
	($1.teacher_fios IS null OR teacher_fio = ANY($1.teacher_fios)) and
    ($1.teacher_bios IS null OR teacher_bio = ANY($1.teacher_bios)) and
	($1.teacher_ids IS null OR teacher_id = ANY($1.teacher_ids)) and
    ($1.subgroup IS null OR lesson_subgroup = $1.subgroup) and
	($1.week IS null OR lesson_week_type = $1.week) and
    ($1.lesson_type is null OR lesson_type = $1.lesson_type) and
    ($1.numbers is null OR lesson_number = ANY($1.numbers))
    ;
    )");
}

std::vector<models::LessonV1> LessonDetailsController::Search(
    const std::optional<models::LessonFilter>& filter) const {
    std::optional<models::TupleLessonFilter> filter_tuple =
        convert::DropPropertiesToConstRefs(filter);
    auto result = pg_cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        qGetLessonsByFilter, filter_tuple);
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
LessonDetailsController::LessonDetailsController(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {
}
}  // namespace timetable_vsu_backend::components::controllers::postgres
