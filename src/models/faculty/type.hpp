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
struct Faculty
{
    convert::Property<boost::uuids::uuid, "id"> id;
    convert::Property<std::string, "name"> name;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace models
