#pragma once
#include <openapi/types/all.hpp>

namespace models
{
using namespace openapi::types;
using namespace openapi::preferences;
struct UserCredentials
{
    String<Name<"login">> login;
    String<Name<"password">> password;
    auto operator<=>(const UserCredentials&) const = default;
};
}  // namespace models
