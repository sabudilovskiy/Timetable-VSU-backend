#pragma once
#include <openapi/base/field.hpp>
#include <openapi/base/properties/datetime.hpp>
#include <openapi/base/property_base.hpp>
#include <openapi/types/array.hpp>
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
    FIELD(lesson_ids, Optional<Array<legacy::models::SubString>>);
    FIELD(begin, Optional<Datetime<>>);
    FIELD(end, Optional<Datetime<>>);
    FIELD(days, Optional<Array<legacy::models::Day>>);
    FIELD(department_ids, Optional<Array<legacy::models::SubString>>);
    FIELD(department_names, Optional<Array<legacy::models::SubString>>);
    FIELD(faculty_ids, Optional<Array<legacy::models::SubString>>);
    FIELD(faculty_names, Optional<Array<legacy::models::SubString>>);
    FIELD(group_ids, Optional<Array<legacy::models::SubString>>);
    FIELD(group_names, Optional<Array<legacy::models::SubString>>);
    FIELD(group_courses, Optional<Array<short>>);
    FIELD(group_types, Optional<Array<legacy::models::EducationType>>);
    FIELD(room_ids, Optional<Array<legacy::models::SubString>>);
    FIELD(room_names, Optional<Array<legacy::models::SubString>>);
    FIELD(subgroup, Optional<legacy::models::Subgroup>);
    FIELD(subject_ids, Optional<Array<legacy::models::SubString>>);
    FIELD(subject_names, Optional<Array<legacy::models::SubString>>);
    FIELD(teacher_ids, Optional<Array<legacy::models::SubString>>);
    FIELD(teacher_fios, Optional<Array<legacy::models::SubString>>);
    FIELD(teacher_bios, Optional<Array<legacy::models::SubString>>);
    Optional<legacy::models::LessonWeekType, Name<"week_type">> week;
    Optional<legacy::models::LessonType, Name<"lesson_type">> type;
    FIELD(numbers, Optional<Array<short>>);
    auto operator<=>(const LessonFilter&) const = default;
};
}  // namespace models
