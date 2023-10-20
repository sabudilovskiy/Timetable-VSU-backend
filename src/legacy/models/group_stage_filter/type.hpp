#pragma once
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <utils/convert/additional_properties.hpp>

#include "legacy/models/day/type.hpp"
#include "legacy/models/education_type/type.hpp"
#include "legacy/models/lesson_type/type.hpp"
#include "legacy/models/lesson_week_type/type.hpp"
#include "legacy/models/subgroup/type.hpp"
#include "legacy/models/substring/type.hpp"
#include "legacy/models/timestring/type.hpp"

namespace legacy::models
{
namespace convert = utils::convert;
struct GroupStageFilter
{
    convert::OptionalArrayProperty<SubString, "group_stage_ids">
        group_stage_ids;
    convert::OptionalArrayProperty<std::int16_t, "group_stage_courses">
        group_stage_courses;
    convert::OptionalProperty<TimeString, "group_stage_begin">
        group_stage_begin;
    convert::OptionalProperty<TimeString, "group_stage_end"> group_stage_end;
    convert::OptionalArrayProperty<SubString, "group_ids"> group_ids;
    convert::OptionalArrayProperty<SubString, "group_names"> group_names;
    convert::OptionalArrayProperty<EducationType, "group_types"> group_types;
    convert::OptionalArrayProperty<SubString, "faculty_ids"> faculty_ids;
    convert::OptionalArrayProperty<SubString, "faculty_names"> faculty_names;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace legacy::models