#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <type_traits>
#include <utils/convert/additional_properties.hpp>

#include "models/day/type.hpp"
#include "models/education_type/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "models/substring/type.hpp"
#include "models/timestring/type.hpp"

namespace models
{
namespace convert = utils::convert;
struct LessonFilter
{
    convert::OptionalArrayProperty<SubString, "lesson_ids"> lesson_ids;
    convert::OptionalProperty<TimeString, "begin"> begin;
    convert::OptionalProperty<TimeString, "end"> end;
    convert::OptionalArrayProperty<Day, "days"> days;
    convert::OptionalArrayProperty<SubString, "department_ids"> department_ids;
    convert::OptionalArrayProperty<SubString, "department_names">
        department_names;
    convert::OptionalArrayProperty<SubString, "faculty_ids"> faculty_ids;
    convert::OptionalArrayProperty<SubString, "faculty_names"> faculty_names;
    convert::OptionalArrayProperty<SubString, "group_ids"> group_ids;
    convert::OptionalArrayProperty<SubString, "group_names"> group_names;
    convert::OptionalArrayProperty<std::int16_t, "group_courses"> group_courses;
    convert::OptionalArrayProperty<models::EducationType, "group_types">
        group_types;
    convert::OptionalArrayProperty<SubString, "room_ids"> room_ids;
    convert::OptionalArrayProperty<SubString, "room_names"> room_names;
    convert::OptionalProperty<Subgroup, "subgroup"> subgroup;
    convert::OptionalArrayProperty<SubString, "subject_ids"> subject_ids;
    convert::OptionalArrayProperty<SubString, "subject_names"> subject_names;
    convert::OptionalArrayProperty<SubString, "teacher_ids"> teacher_ids;
    convert::OptionalArrayProperty<SubString, "teacher_fios"> teacher_fios;
    convert::OptionalArrayProperty<SubString, "teacher_bios"> teacher_bios;
    convert::OptionalProperty<LessonWeekType, "week_type"> week;
    convert::OptionalProperty<LessonType, "lesson_type"> type;
    convert::OptionalArrayProperty<std::int16_t, "numbers"> numbers;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace models
