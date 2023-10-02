#pragma once
#include <boost/uuid/uuid.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/json_serialize.hpp>

namespace timetable_vsu_backend::models
{
using namespace utils::convert;
struct AdminAccount
{
    Property<boost::uuids::uuid, "user_id"> user_id;
    Property<boost::uuids::uuid, "admin_id"> admin_id;
    Property<std::string, "login"> credentials;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
};
static_assert(JsonSeriazable<AdminAccount>);
}  // namespace timetable_vsu_backend::models
