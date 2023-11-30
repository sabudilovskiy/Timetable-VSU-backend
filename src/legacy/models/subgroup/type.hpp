#pragma once

#include <openapi/enum/declare.hpp>
namespace legacy::models
{
// enum struct Subgroup : int
// {
//     all,
//     first,
//     second
// };
// struct enum_introspector_Subgroup;
// consteval enum_introspector_Subgroup* get_enum_introspector(
//     std ::type_identity<Subgroup>)
// {
//     return nullptr;
// }
// struct enum_introspector_Subgroup
// {
//     using enum Subgroup;
//     static constexpr std::array<std::string_view, 3> names = {"all", "first",
//                                                               "second"};
//     static constexpr std::array<Subgroup, 3> values = {all, first, second};
// };

DECLARE_OPENAPI_ENUM(Subgroup, int, 
    all,
    even,
    odd);
}  // namespace legacy::models
