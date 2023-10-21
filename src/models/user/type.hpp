#pragma once
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
    Property<legacy::models::UserType, openapi::NamedTraits<"type">> type;
    auto operator<=>(const User&) const = default;
};

}  // namespace models
