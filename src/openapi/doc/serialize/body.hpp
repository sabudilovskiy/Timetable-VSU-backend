#pragma once

#include <openapi/doc/serialize/base.hpp>
#include <openapi/http/base/body_property.hpp>

namespace openapi
{
template <typename T, typename Traits>
void AppendRequestField(DocHelper doc_helper,
                        std::type_identity<http::BodyProperty<T, Traits>>)
{
    auto& [root, cur] = doc_helper;
    auto request_body_node = cur["requestBody"];
    if (!request_body_node.IsObject())
    {
        request_body_node = userver::formats::yaml::Type::kObject;
    }
    request_body_node["required"] = !userver::meta::kIsOptional<T>;
    auto content = request_body_node["content"];
    if (!content.IsObject())
    {
        content = userver::formats::yaml::Type::kObject;
    }
    auto application_json_node = content["application/json"];
    if (application_json_node.IsObject())
    {
        application_json_node = userver::formats::yaml::Type::kObject;
    }
    auto schema = application_json_node["schema"];
    Append(DocHelper{doc_helper.root, schema}, std::type_identity<T>{});
}

template <typename T, typename Traits>
void AppendResponseField(DocHelper doc_helper,
                         std::type_identity<http::BodyProperty<T, Traits>>)
{
    auto& [root, cur] = doc_helper;
    auto schema = cur["content"]["application/json"]["schema"];
    Append(DocHelper{doc_helper.root, schema}, std::type_identity<T>{});
}
}  // namespace openapi
