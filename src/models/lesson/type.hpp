#pragma once
#include <boost/uuid/uuid.hpp>

#include "utils/convert/base.hpp"

namespace convert = timetable_vsu_backend::utils::convert;

struct LessonV1 {
    convert::Property<boost::uuids::uuid, "room_id"> room_id;
    convert::Property<std::string, "room_name"> room_name;
    convert::Property<boost::uuids::uuid, "teacher_id"> teacher_id;
    convert::Property<std::string, "teacher_fio"> teacher_fio;
    convert::Property<boost::uuids::uuid, "subject_id"> subject_id;
    convert::Property<std::string, "subject_name"> subject_name;
};