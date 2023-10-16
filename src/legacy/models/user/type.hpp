#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/utils/strong_typedef.hpp>
#include <utils/convert/base.hpp>

#include "legacy/models/user_type/type.hpp"

namespace legacy::models
{
namespace convert = utils::convert;
struct User
{
    convert::Property<boost::uuids::uuid, "id"> id;
    convert::Property<legacy::models::UserType, "type"> type;
    static constexpr convert::PolicyFields kPolicyFields =
        convert::PolicyFields::ConvertAll;
};

static_assert(utils::convert::IsConvertAll<User>);
}  // namespace legacy::models
