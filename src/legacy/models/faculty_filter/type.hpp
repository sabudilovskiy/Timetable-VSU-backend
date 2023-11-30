#pragma once
#include <boost/uuid/uuid.hpp>
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
struct FacultyFilter
{
    convert::OptionalArrayProperty<SubString, "ids"> ids;
    convert::OptionalArrayProperty<SubString, "names"> names;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace legacy::models
