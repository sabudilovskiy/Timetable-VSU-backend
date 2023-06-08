#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <type_traits>

#include "models/day/type.hpp"
#include "models/education_type/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "models/substring/type.hpp"
#include "models/timestring/type.hpp"
#include "utils/convert/additional_properties.hpp"

namespace timetable_vsu_backend::models
{
namespace convert = utils::convert;
struct Faculty
{
    convert::Property<boost::uuids::uuid, "id"> id;
    convert::Property<std::string, "name"> name;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
