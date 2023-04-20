#pragma once
#include <boost/uuid/uuid.hpp>
#include <chrono>

#include "models/day/type.hpp"
#include "models/education_type/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "models/timestring/type.hpp"
#include "utils/convert/base.hpp"

namespace convert = timetable_vsu_backend::utils::convert;

namespace timetable_vsu_backend::models {
// type for API
struct LessonV1 {
    convert::Property<boost::uuids::uuid, "id"> lesson_id;
    convert::Property<TimeString, "begin"> lesson_begin;
    convert::Property<TimeString, "end"> lesson_end;
    convert::Property<short, "number"> lesson_number;
    convert::Property<LessonType, "type"> lesson_type;
    convert::Property<LessonWeekType, "week_type"> lesson_week_type;
    convert::Property<Subgroup, "subgroup"> lesson_subgroup;
    convert::Property<Day, "day"> lesson_day;
    convert::Property<boost::uuids::uuid, "room_id"> room_id;
    convert::Property<std::string, "room_name"> room_name;
    convert::Property<boost::uuids::uuid, "subject_id"> subject_id;
    convert::Property<std::string, "subject_name"> subject_name;
    convert::Property<boost::uuids::uuid, "group_id"> group_id;
    convert::Property<short, "group_course"> group_stage_course;
    convert::Property<std::string, "group_name"> group_name;
    convert::Property<EducationType, "group_type"> group_type;
    convert::Property<boost::uuids::uuid, "faculty_id"> faculty_id;
    convert::Property<std::string, "faculty_name"> faculty_name;
    convert::Property<boost::uuids::uuid, "department_id"> department_id;
    convert::Property<std::string, "department_name"> department_name;
    convert::Property<boost::uuids::uuid, "teacher_id"> teacher_id;
    convert::Property<std::string, "teacher_fio"> teacher_fio;
    convert::Property<std::string, "teacher_bio"> teacher_bio;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models