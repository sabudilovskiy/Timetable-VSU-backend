#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/utils/strong_typedef.hpp>

#include "models/user_type/type.hpp"
#include "utils/convert/base.hpp"

namespace timetable_vsu_backend::models
{
namespace convert = utils::convert;
struct Teacher
{
    convert::Property<boost::uuids::uuid, "id"> id;
    convert::Property<std::string, "fio"> fio;
    convert::Property<std::string, "bio"> bio;
    convert::Property<boost::uuids::uuid, "department_id"> department_id;
    convert::Property<std::string, "department_name"> department_name;
    convert::Property<boost::uuids::uuid, "faculty_id"> faculty_id;
    convert::Property<std::string, "faculty_name"> faculty_name;
    static constexpr convert::PolicyFields kPolicyFields =
        convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
