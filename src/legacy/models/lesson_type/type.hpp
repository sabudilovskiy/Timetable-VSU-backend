#pragma once

#include <openapi/enum/declare.hpp>
namespace legacy::models
{
// DECLARE_OPENAPI_ENUM(LessonType, int, labaratory, lection, practice,
// some_test,
//                      some_test2, some_test3);
enum struct LessonType : int
{
    labaratory,
    lection,
    practice
};
struct enum_introspector_LessonType;
consteval enum_introspector_LessonType* get_enum_introspector(
    std ::type_identity<LessonType>)
{
    return nullptr;
}
struct enum_introspector_LessonType
{
    using enum LessonType;
    static constexpr std::array<std::string_view, 3> names = {
        "labaratory", "lection", "practice"};
    static constexpr std::array<LessonType, 3> values = {labaratory, lection,
                                                         practice};
};
}  // namespace legacy::models
