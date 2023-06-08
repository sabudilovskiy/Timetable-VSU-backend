#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/utils/strong_typedef.hpp>

#include "models/user_type/type.hpp"
#include "utils/convert/base.hpp"

namespace timetable_vsu_backend::models
{
namespace convert = utils::convert;
struct TeacherInfo
{
    convert::Property<std::string, "fio"> fio;
    convert::Property<std::string, "bio"> bio;
    convert::Property<boost::uuids::uuid, "department_id"> department_id;
    static constexpr convert::PolicyFields kPolicyFields =
        convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
