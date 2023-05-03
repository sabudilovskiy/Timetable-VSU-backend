#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <type_traits>

#include "models/day/type.hpp"
#include "models/education_type/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "models/timestring/type.hpp"
#include "utils/convert/additional_properties.hpp"

namespace timetable_vsu_backend::models {
namespace convert = utils::convert;
struct LessonFilter {
    convert::OptionalArrayProperty<boost::uuids::uuid, "lesson_ids"> lesson_ids;
    convert::OptionalProperty<TimeString, "begin"> begin;
    convert::OptionalProperty<TimeString, "end"> end;
    convert::OptionalArrayProperty<Day, "days"> days;
    convert::OptionalArrayProperty<boost::uuids::uuid, "department_ids">
        department_ids;
    convert::OptionalArrayProperty<std::string, "department_names">
        department_names;
    convert::OptionalArrayProperty<boost::uuids::uuid, "faculty_ids">
        faculty_ids;
    convert::OptionalArrayProperty<std::string, "faculty_names"> faculty_names;
    convert::OptionalArrayProperty<boost::uuids::uuid, "group_ids"> group_ids;
    convert::OptionalArrayProperty<std::string, "group_names"> group_names;
    convert::OptionalArrayProperty<std::int16_t, "group_courses"> group_courses;
    convert::OptionalArrayProperty<models::EducationType, "group_types">
        group_types;
    convert::OptionalArrayProperty<boost::uuids::uuid, "room_ids"> room_ids;
    convert::OptionalArrayProperty<std::string, "room_names"> room_names;
    convert::OptionalProperty<Subgroup, "subgroup"> subgroup;
    convert::OptionalArrayProperty<boost::uuids::uuid, "subject_ids">
        subject_ids;
    convert::OptionalArrayProperty<std::string, "subject_names"> subject_names;
    convert::OptionalArrayProperty<boost::uuids::uuid, "teacher_ids">
        teacher_ids;
    convert::OptionalArrayProperty<std::string, "teacher_fios"> teacher_fios;
    convert::OptionalArrayProperty<std::string, "teacher_bios"> teacher_bios;
    convert::OptionalProperty<LessonWeekType, "week_type"> week;
    convert::OptionalProperty<LessonType, "lesson_type"> type;
    convert::OptionalArrayProperty<std::int16_t, "numbers"> numbers;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
