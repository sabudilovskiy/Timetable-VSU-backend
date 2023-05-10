#pragma once
#include <boost/uuid/uuid.hpp>

#include "utils/convert/base.hpp"

namespace timetable_vsu_backend::models {
using namespace utils::convert;
struct AdminAccount {
    Property<boost::uuids::uuid, "user_id"> user_id;
    Property<boost::uuids::uuid, "admin_id"> admin_id;
    Property<std::string, "login"> credentials;
    Property<std::string, "password"> password;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
