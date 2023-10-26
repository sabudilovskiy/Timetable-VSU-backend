#pragma once
#include <openapi/base/named_traits.hpp>
#include <openapi/types/datetime.hpp>
#include <openapi/types/field.hpp>
#include <openapi/types/string.hpp>
#include <openapi/types/uuid.hpp>

#include "legacy/models/day/type.hpp"
#include "legacy/models/education_type/type.hpp"
#include "legacy/models/lesson_type/type.hpp"
#include "legacy/models/lesson_week_type/type.hpp"
#include "legacy/models/subgroup/type.hpp"
#include "legacy/models/user_type/type.hpp"

namespace models
{
using namespace openapi::types;
using namespace openapi::preferences;
struct LessonV1
{
    Uuid<Name<"id">> lesson_id;
    Datetime<Name<"begin">> lesson_begin;
    Datetime<Name<"end">> lesson_end;
    Field<short, Name<"number">> lesson_number;
    Field<legacy::models::LessonType, Name<"type">> lesson_type;
    Field<legacy::models::LessonWeekType, Name<"week_type">> lesson_week_type;
    Field<legacy::models::Subgroup, Name<"subgroup">> lesson_subgroup;
    Field<legacy::models::Day, Name<"day">> lesson_day;
    Uuid<Name<"room_id">> room_id;
    String<Name<"room_name">> room_name;
    Uuid<Name<"subject_id">> subject_id;
    String<Name<"subject_name">> subject_name;
    Uuid<Name<"group_id">> group_id;
    Field<short, Name<"group_course">> group_stage_course;
    String<Name<"group_name">> group_name;
    Field<legacy::models::EducationType, Name<"group_type">> group_type;
    Uuid<Name<"faculty_id">> faculty_id;
    String<Name<"faculty_name">> faculty_name;
    Uuid<Name<"department_id">> department_id;
    String<Name<"department_name">> department_name;
    Uuid<Name<"teacher_id">> teacher_id;
    String<Name<"teacher_fio">> teacher_fio;
    String<Name<"teacher_bio">> teacher_bio;
    auto operator<=>(const LessonV1&) const = default;
};

}  // namespace models
