#pragma once
#include "models/lesson_type/type.hpp"
#include "models/lesson_v1/type.hpp"
#include "models/lesson_with_details/type.hpp"

namespace timetable_vsu_backend::helpers {
inline models::LessonV1 ConvertLesson(models::LessonWithDetails&& lesson) {
    return models::LessonV1{
        .lesson_id = {lesson.lesson_id},
        .lesson_begin = {lesson.lesson_begin},
        .lesson_end = {lesson.lesson_end},
        .lesson_number = {lesson.lesson_number},
        .lesson_type = {lesson.lesson_type},
        .lesson_week_type = {lesson.lesson_week_type},
        .lesson_subgroup = {lesson.lesson_subgroup},
        .lesson_day = {lesson.lesson_day},
        .room_id = {lesson.room_id},
        .room_name = {std::move(lesson.room_name)},
        .subject_id = {lesson.subject_id},
        .subject_name = {std::move(lesson.subject_name)},
        .group_id = {lesson.group_id},
        .group_stage_course = {lesson.group_stage_course},
        .group_name = {std::move(lesson.group_name)},
        .group_type = {lesson.group_type},
        .faculty_id = {lesson.faculty_id},
        .faculty_name = {std::move(lesson.faculty_name)},
        .department_id = {lesson.department_id},
        .department_name = {std::move(lesson.department_name)},
        .teacher_id = {lesson.teacher_id},
        .teacher_fio = {std::move(lesson.teacher_fio)},
        .teacher_bio = {std::move(lesson.teacher_bio)}};
}
}  // namespace timetable_vsu_backend::helpers