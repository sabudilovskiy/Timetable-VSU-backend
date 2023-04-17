#pragma once
#include <boost/uuid/uuid.hpp>
#include <chrono>

#include "models/education_type/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "utils/convert/base.hpp"

namespace convert = timetable_vsu_backend::utils::convert;

namespace timetable_vsu_backend::models {
// type for API
struct LessonV1 {
    convert::Property<boost::uuids::uuid, "lesson_id"> lesson_id;
    convert::Property<boost::uuids::uuid, "lesson_begin"> lesson_begin;
    convert::Property<std::chrono::system_clock::time_point, "lesson_end">
        lesson_end;
    convert::Property<std::chrono::system_clock::time_point, "lesson_number">
        lesson_number;
    convert::Property<LessonType, "lesson_type"> lesson_type;
    convert::Property<LessonWeekType, "lesson_week_type"> lesson_week_type;
    convert::Property<Subgroup, "lesson_subgroup"> lesson_subgroup;
    convert::Property<boost::uuids::uuid, "room_id"> room_id;
    convert::Property<std::string, "room_name"> room_name;
    convert::Property<boost::uuids::uuid, "subject_id"> subject_id;
    convert::Property<std::string, "subject_name"> subject_name;
    convert::Property<boost::uuids::uuid, "group_id"> group_id;
    convert::Property<short, "group_stage_course"> group_stage_course;
    convert::Property<std::string, "group_name"> group_name;
    convert::Property<EducationType, "group_type"> group_type;
    convert::Property<boost::uuids::uuid, "faculty_id"> faculty_id;
    convert::Property<std::string, "faculty_name"> faculty_name;
    convert::Property<boost::uuids::uuid, "department_id"> department_id;
    convert::Property<std::string, "department_name"> department_name;
    convert::Property<boost::uuids::uuid, "teacher_id"> teacher_id;
    convert::Property<std::string, "teacher_fio"> teacher_fio;
    convert::Property<std::string, "teacher_bio"> teacher_bio;
};
}  // namespace timetable_vsu_backend::models