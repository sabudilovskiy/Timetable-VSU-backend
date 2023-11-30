#pragma once
#include <openapi/enum/declare.hpp>

namespace legacy::models
{
DECLARE_OPENAPI_ENUM(LessonWeekType, int, all, even, odd);
// enum struct LessonWeekType : int
// {
//     all,
//     even,
//     odd
// };
// struct enum_introspector_LessonWeekType;
// consteval enum_introspector_LessonWeekType* get_enum_introspector(
//     std ::type_identity<LessonWeekType>)
// {
//     return nullptr;
// }
// struct enum_introspector_LessonWeekType
// {
//     using enum LessonWeekType;
//     static constexpr std::array<std::string_view, 3> names = {"all", "even",
//                                                               "odd"};
//     static constexpr std::array<LessonWeekType, 3> values = {all, even, odd};
// };
}  // namespace legacy::models
