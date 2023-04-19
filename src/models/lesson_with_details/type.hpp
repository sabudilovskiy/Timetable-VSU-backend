#pragma once
#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <string>

#include "models/day/type.hpp"
#include "models/education_type/type.hpp"
#include "models/lesson_type/type.hpp"
#include "models/lesson_week_type/type.hpp"
#include "models/subgroup/type.hpp"
#include "models/timestring/type.hpp"

namespace timetable_vsu_backend::models {
// postgres type
struct LessonWithDetails {
    boost::uuids::uuid lesson_id;
    boost::uuids::uuid lesson_begin;
    TimeString lesson_end;
    TimeString lesson_number;
    LessonType lesson_type;
    LessonWeekType lesson_week_type;
    Subgroup lesson_subgroup;
    Day lesson_day;
    boost::uuids::uuid room_id;
    std::string room_name;
    boost::uuids::uuid subject_id;
    std::string subject_name;
    boost::uuids::uuid group_id;
    short group_stage_course;
    std::string group_name;
    EducationType group_type;
    boost::uuids::uuid faculty_id;
    std::string faculty_name;
    boost::uuids::uuid department_id;
    std::string department_name;
    boost::uuids::uuid teacher_id;
    std::string teacher_fio;
    std::string teacher_bio;
};

}  // namespace timetable_vsu_backend::models
