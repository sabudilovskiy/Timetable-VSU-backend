#pragma once
#include <boost/pfr/core.hpp>
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <type_traits>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/day/type.hpp"
#include "legacy/models/education_type/type.hpp"
#include "legacy/models/lesson_type/type.hpp"
#include "legacy/models/lesson_week_type/type.hpp"
#include "legacy/models/subgroup/type.hpp"
#include "legacy/models/substring/postgre.hpp"
#include "legacy/models/substring/type.hpp"
#include "legacy/models/timestring/type.hpp"

namespace legacy::models
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
}  // namespace legacy::models
