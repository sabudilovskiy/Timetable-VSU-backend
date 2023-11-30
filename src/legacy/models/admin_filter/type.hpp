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
struct AdminFilter
{
    convert::OptionalArrayProperty<SubString, "admin_ids"> admin_ids;
    convert::OptionalArrayProperty<SubString, "user_ids"> user_ids;
    convert::OptionalArrayProperty<SubString, "logins"> logins;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace legacy::models
