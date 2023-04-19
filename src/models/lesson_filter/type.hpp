#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>

#include "models/day/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "utils/convert/additional_properties.hpp"

namespace timetable_vsu_backend::models {
namespace convert = utils::convert;
struct LessonFilter {
    convert::OptionalProperty<std::vector<Day>, "days"> days;
    convert::OptionalProperty<boost::uuids::uuid, "department_id">
        department_id;
    convert::OptionalProperty<std::string, "department_name"> department_name;
    convert::OptionalProperty<boost::uuids::uuid, "faculty_id"> faculty_id;
    convert::OptionalProperty<std::string, "faculty_name"> faculty_name;
    convert::OptionalProperty<boost::uuids::uuid, "group_id"> group_id;
    convert::OptionalProperty<std::string, "group_name"> group_name;
    convert::OptionalProperty<std::string, "room_name"> room_name;
    convert::OptionalProperty<Subgroup, "subgroup"> subgroup;
    convert::OptionalProperty<std::string, "subject_name"> subject_name;
    convert::OptionalProperty<std::string, "teacher_fio"> teacher_fio;
    convert::OptionalProperty<boost::uuids::uuid, "teacher_id"> teacher_id;
    convert::OptionalProperty<LessonWeekType, "week"> week;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models