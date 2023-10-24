#pragma once
#include <openapi/base/enum/declare.hpp>

namespace legacy::models
{
// clang-format off
DECLARE_OPENAPI_ENUM(UserType, int, 
    user, 
    admin, 
    root, 
    teacher);
// clang-format on
}  // namespace legacy::models
