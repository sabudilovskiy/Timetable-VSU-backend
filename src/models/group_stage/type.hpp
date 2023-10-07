#pragma once
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>

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
struct GroupStage
{
    convert::Property<boost::uuids::uuid, "group_stage_id"> group_stage_id;
    convert::Property<std::int16_t, "group_stage_course"> group_stage_course;
    convert::Property<TimeString, "group_stage_begin"> group_stage_begin;
    convert::Property<TimeString, "group_stage_end"> group_stage_end;
    convert::Property<boost::uuids::uuid, "group_id"> group_id;
    convert::Property<std::string, "group_name"> group_name;
    convert::Property<EducationType, "group_type"> group_type;
    convert::Property<boost::uuids::uuid, "faculty_id"> faculty_id;
    convert::Property<std::string, "faculty_name"> faculty_name;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace models
