#pragma once
#include <openapi/base/field.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/types/uuid.hpp>

#include "legacy/models/user_type/type.hpp"

namespace models
{
using namespace openapi::types;
using namespace openapi::preferences;
struct User
{
    Uuid<Name<"id">> id;
    FIELD(type, legacy::models::UserType);
    auto operator<=>(const User&) const = default;
};

}  // namespace models
