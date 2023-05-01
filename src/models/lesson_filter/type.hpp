#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <type_traits>

#include "models/day/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "utils/convert/additional_properties.hpp"

namespace timetable_vsu_backend::models {
namespace convert = utils::convert;
struct LessonFilter {
    convert::OptionalArrayProperty<Day, "days"> days;
    convert::OptionalArrayProperty<boost::uuids::uuid, "department_ids">
        department_id;
    convert::OptionalArrayProperty<std::string, "department_names">
        department_names;
    convert::OptionalArrayProperty<boost::uuids::uuid, "faculty_ids">
        faculty_ids;
    convert::OptionalArrayProperty<std::string, "faculty_names"> faculty_names;
    convert::OptionalArrayProperty<boost::uuids::uuid, "group_ids"> group_ids;
    convert::OptionalArrayProperty<std::string, "group_names"> group_names;
    convert::OptionalArrayProperty<std::string, "room_names"> room_names;
    convert::OptionalProperty<Subgroup, "subgroup"> subgroup;
    convert::OptionalArrayProperty<std::string, "subject_names"> subject_names;
    convert::OptionalArrayProperty<std::string, "teacher_fios"> teacher_fios;
    convert::OptionalArrayProperty<boost::uuids::uuid, "teacher_ids">
        teacher_ids;
    convert::OptionalProperty<LessonWeekType, "week_type"> week;
    convert::OptionalProperty<LessonType, "lesson_type"> type;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};

static_assert(std::is_aggregate_v<LessonFilter>, "");
}  // namespace timetable_vsu_backend::models