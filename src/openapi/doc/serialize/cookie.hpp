#pragma once

#include <openapi/doc/serialize/base.hpp>
#include <openapi/http/base/cookie_property.hpp>
#include <utils/compilers_macros.hpp>

namespace openapi
{
template <typename T, typename Traits>
void AppendRequestField(DocHelper doc_helper,
                        std::type_identity<http::CookieProperty<T, Traits>>)
{
    auto& [root, cur] = doc_helper;
    auto parameters_node = cur["parameters"];
    if (!parameters_node.IsArray())
    {
        parameters_node = userver::formats::yaml::Type::kArray;
    }
    static_assert(!traits::GetName<Traits>().empty(), "Cookie must have name");
    userver::formats::yaml::ValueBuilder parameter_node =
        userver::formats::yaml::Type::kObject;
    parameter_node["in"] = "cookie";
    parameter_node["name"] = traits::GetName<Traits>().AsString();
    parameter_node["required"] = userver::meta::kIsOptional<T>;
    auto schema = parameter_node["schema"];
    Append(DocHelper{doc_helper.root, schema}, std::type_identity<T>{});
    parameters_node.PushBack(std::move(parameter_node));
}

template <typename T, typename Traits>
void AppendResponseField(DocHelper,
                         std::type_identity<http::CookieProperty<T, Traits>>)
{
    STATIC_ASSERT_FALSE(
        "OpenApi 3.0 doesnt support cookie in reponse. Sorry :(");
}

}  // namespace openapi
