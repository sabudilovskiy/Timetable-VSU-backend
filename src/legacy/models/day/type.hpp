#pragma once
#include <openapi/enum/declare.hpp>

namespace legacy::models
{
// enum struct Day : int
// {
//     monday,
//     tuesday,
//     wednesday,
//     thursday,
//     friday,
//     saturday
// };
// struct enum_introspector_Day;
// consteval enum_introspector_Day* get_enum_introspector(std ::type_identity<Day>)
// {
//     return nullptr;
// }
// struct enum_introspector_Day
// {
//     using enum Day;
//     static constexpr std::array<std::string_view, 6> names = {
//         "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
//     static constexpr std::array<Day, 6> values = {monday,   tuesday, wednesday,
//                                                   thursday, friday,  saturday};
// };
DECLARE_OPENAPI_ENUM(Day, int,     
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday);
}  // namespace legacy::models
