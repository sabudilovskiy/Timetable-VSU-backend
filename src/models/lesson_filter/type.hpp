#pragma once
#include <openapi/base/properties/datetime.hpp>
#include <openapi/base/property_base.hpp>
#include <openapi/types/datetime.hpp>
#include <openapi/types/optional.hpp>
#include <vector>

#include "legacy/models/day/type.hpp"
#include "legacy/models/education_type/type.hpp"
#include "legacy/models/lesson_type/type.hpp"
#include "legacy/models/lesson_week_type/type.hpp"
#include "legacy/models/subgroup/type.hpp"
#include "legacy/models/substring/type.hpp"

namespace models
{
using namespace openapi::types;
using namespace openapi::preferences;

struct LessonFilter
{
    Optional<std::vector<legacy::models::SubString>, Name<"lesson_ids">>
        lesson_ids;
    Optional<Datetime<>, Name<"begin">> begin;
    Optional<Datetime<>, Name<"end">> end;
    Optional<std::vector<legacy::models::Day>, Name<"days">> days;
    Optional<std::vector<legacy::models::SubString>, Name<"department_ids">>
        department_ids;
    Optional<std::vector<legacy::models::SubString>, Name<"department_names">>
        department_names;
    Optional<std::vector<legacy::models::SubString>, Name<"faculty_ids">>
        faculty_ids;
    Optional<std::vector<legacy::models::SubString>, Name<"faculty_names">>
        faculty_names;
    Optional<std::vector<legacy::models::SubString>, Name<"group_ids">>
        group_ids;
    Optional<std::vector<legacy::models::SubString>, Name<"group_names">>
        group_names;
    Optional<std::vector<short>, Name<"group_courses">> group_courses;
    Optional<std::vector<legacy::models::EducationType>, Name<"group_types">>
        group_types;
    Optional<std::vector<legacy::models::SubString>, Name<"room_ids">> room_ids;
    Optional<std::vector<legacy::models::SubString>, Name<"room_names">>
        room_names;
    Optional<legacy::models::Subgroup, Name<"subgroup">> subgroup;
    Optional<std::vector<legacy::models::SubString>, Name<"subject_ids">>
        subject_ids;
    Optional<std::vector<legacy::models::SubString>, Name<"subject_names">>
        subject_names;
    Optional<std::vector<legacy::models::SubString>, Name<"teacher_ids">>
        teacher_ids;
    Optional<std::vector<legacy::models::SubString>, Name<"teacher_fios">>
        teacher_fios;
    Optional<std::vector<legacy::models::SubString>, Name<"teacher_bios">>
        teacher_bios;
    Optional<legacy::models::LessonWeekType, Name<"week_type">> week;
    Optional<legacy::models::LessonType, Name<"lesson_type">> type;
    Optional<std::vector<short>, Name<"numbers">> numbers;
    auto operator<=>(const LessonFilter&) const = default;
};
}  // namespace models
