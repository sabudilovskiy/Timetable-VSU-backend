#pragma once

#include <openapi/base/named_traits.hpp>
#include <openapi/doc/serialize/base.hpp>

namespace timetable_vsu_backend::openapi
{
template <typename T, typename Traits>
void AppendRequestField(DocHelper doc_helper,
                        std::type_identity<http::HeaderProperty<T, Traits>>)
{
    auto& [root, cur] = doc_helper;
    auto parameters_node = cur["parameters"];
    if (!parameters_node.IsArray())
    {
        parameters_node = userver::formats::yaml::Type::kArray;
    }
    static_assert(!traits::GetName<Traits>().empty(), "Header must have name");
    userver::formats::yaml::ValueBuilder parameter_node =
        userver::formats::yaml::Type::kObject;
    parameter_node["in"] = "header";
    parameter_node["name"] = traits::GetName<Traits>().AsString();
    parameter_node["required"] = userver::meta::kIsOptional<T>;
    auto schema = parameter_node["schema"];
    Append(DocHelper{doc_helper.root, schema}, std::type_identity<T>{});
    parameters_node.PushBack(std::move(parameter_node));
}

template <typename T, typename Traits>
void AppendResponseField(DocHelper doc_helper,
                         std::type_identity<http::HeaderProperty<T, Traits>>)
{
    auto& [root, cur] = doc_helper;
    constexpr auto name = traits::GetName<Traits>();
    static_assert(!name.empty(), "Header must have name");
    auto name_s = name.AsString();
    auto header = cur["headers"][name_s]["schema"];
    Append(DocHelper{doc_helper.root, header}, std::type_identity<T>{});
}
}  // namespace timetable_vsu_backend::openapi
