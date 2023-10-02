#pragma once
#include <boost/uuid/uuid.hpp>
#include <utils/convert/base.hpp>
namespace timetable_vsu_backend::models
{
struct RequestPrivileges
{
    utils::convert::Property<boost::uuids::uuid, "request_id"> request_id;
    utils::convert::Property<boost::uuids::uuid, "user_id"> user_id;
    utils::convert::Property<std::string, "description"> description;
    static constexpr utils::convert::PolicyFields kPolicyFields =
        utils::convert::PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
