#pragma once
#include <openapi/enum/declare.hpp>

namespace legacy::models
{
enum struct EducationType : int
{
    undergraduate,
    magistracy,
    postgraduate,
    specialty
};
struct enum_introspector_EducationType;
consteval enum_introspector_EducationType* get_enum_introspector(
    std ::type_identity<EducationType>)
{
    return nullptr;
}
struct enum_introspector_EducationType
{
    using enum EducationType;
    static constexpr std::array<std::string_view, 4> names = {
        "undergraduate", "magistracy", "postgraduate", "specialty"};
    static constexpr std::array<EducationType, 4> values = {
        undergraduate, magistracy, postgraduate, specialty};
};
// DECLARE_OPENAPI_ENUM(EducationType, int, undergraduate, magistracy,
//                      postgraduate, specialty);
}  // namespace legacy::models
