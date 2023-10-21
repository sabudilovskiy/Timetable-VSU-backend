#pragma once
#include <openapi/base/named_traits.hpp>
#include <openapi/types/string.hpp>
#include <openapi/types/uuid.hpp>

#include "legacy/models/user_type/type.hpp"

namespace models
{
using namespace openapi::types;
using namespace openapi::preferences;
struct LessonV1
{
    Uuid<Name<"id">> lesson_id;
    convert::Property<TimeString, "begin"> lesson_begin;
    convert::Property<TimeString, "end"> lesson_end;
    convert::Property<short, "number"> lesson_number;
    convert::Property<LessonType, "type"> lesson_type;
    convert::Property<LessonWeekType, "week_type"> lesson_week_type;
    convert::Property<Subgroup, "subgroup"> lesson_subgroup;
    convert::Property<Day, "day"> lesson_day;
    Uuid<Name<"room_id">> room_id;
    String<Name<"room_name">> room_name;
    Uuid<Name<"subject_id">> subject_id;
    String < Name<"subject_name"> subject_name;
    Uuid<Name<"group_id">> group_id;
    convert::Property<short, "group_course"> group_stage_course;
    String < Name<"group_name"> group_name;
    convert::Property<EducationType, "group_type"> group_type;
    Uuid<Name<"faculty_id">> faculty_id;
    String < Name<"faculty_name"> faculty_name;
    Uuid<Name<"department_id">> department_id;
    String < Name<"department_name"> department_name;
    Uuid<Name<"teacher_id">> teacher_id;
    String<Name<"teacher_fio">> teacher_fio;
    String<Name<"teacher_bio">> teacher_bio;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
};

}  // namespace models
