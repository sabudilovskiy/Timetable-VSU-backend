#pragma once
#include <openapi/enum/declare.hpp>

namespace legacy::models
{
// clang-format off
DECLARE_OPENAPI_ENUM(UserType, int, 
    user, 
    admin, 
    root, 
    teacher);
// clang-format on

// enum struct UserType : int
// {
//     user,
//     admin,
//     root,
//     teacher
// };
// struct enum_introspector_UserType;
// consteval enum_introspector_UserType* get_enum_introspector(
//     std ::type_identity<UserType>)
// {
//     return nullptr;
// }
// struct enum_introspector_UserType
// {
//     using enum UserType;
//     static constexpr std::array<std::string_view, 4> names = {
//         "user", "admin", "root", "teacher"};
//     static constexpr std::array<UserType, 4> values = {user, admin, root,
//                                                        teacher};
// };
}  // namespace legacy::models
