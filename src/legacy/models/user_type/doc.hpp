#pragma once
#include <openapi/doc/base.hpp>

#include "type.hpp"

namespace openapi
{
template <>
inline std::string GetOpenApiTypeName<legacy::models::UserType>()
{
    return "models.UserType";
}

inline void Append(DocHelper doc_helper,
                   std::type_identity<legacy::models::UserType>)
{
    auto name = GetOpenApiTypeName<legacy::models::UserType>();
    PlaceRefToType<legacy::models::UserType>(doc_helper.cur_place);
    auto type_node = doc_helper.root["components"]["schemas"][name];
    type_node["type"] = "string";
    auto enum_node = type_node["enum"];
    enum_node = userver::formats::yaml::Type::kArray;
    enum_node.Resize(4);
    enum_node[0] = "root";
    enum_node[1] = "admin";
    enum_node[2] = "teacher";
    enum_node[3] = "user";
}
}  // namespace openapi
