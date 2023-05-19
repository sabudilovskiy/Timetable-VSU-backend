#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <type_traits>

#include "models/day/type.hpp"
#include "models/education_type/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "models/substring/postgre.hpp"
#include "models/substring/type.hpp"
#include "models/timestring/type.hpp"
#include "utils/convert/additional_properties.hpp"

namespace timetable_vsu_backend::models
{
namespace convert = utils::convert;
struct TeacherFilter
{
    convert::OptionalArrayProperty<SubString, "teacher_ids"> admin_ids;
    convert::OptionalArrayProperty<SubString, "teacher_fios"> fios;
    convert::OptionalArrayProperty<SubString, "teacher_bios"> bios;
    convert::OptionalArrayProperty<SubString, "department_ids"> department_ids;
    convert::OptionalArrayProperty<SubString, "department_names">
        department_names;
    convert::OptionalArrayProperty<SubString, "faculty_ids"> faculty_ids;
    convert::OptionalArrayProperty<SubString, "faculty_names"> faculty_names;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
