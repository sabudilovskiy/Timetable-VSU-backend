#pragma once
#include <openapi/doc/base.hpp>
#include <openapi/enum/declare.hpp>

namespace openapi
{
template <typename T>
void Append(DocHelper doc_helper,
            std::type_identity<T>) requires HasIntrospector<T>
{
    if (&doc_helper.cur_place != &doc_helper.root)
    {
        PlaceRefToType<T>(doc_helper.cur_place);
    }
    auto field_node =
        doc_helper.root["components"]["schemas"][GetOpenApiTypeName<T>()];
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "string";
    userver::formats::yaml::ValueBuilder enum_node = field_node["enum"];
    enum_node = userver::formats::yaml::Type::kArray;
    for (auto name : enum_introspector<T>::names)
    {
        enum_node.PushBack(std::string(name));
    }
}
}  // namespace openapi
