#pragma once
#include <openapi/doc/serialize/base.hpp>

namespace timetable_vsu_backend::openapi
{
template <typename T, typename Traits>
void Append(DocHelper doc_helper,
            std::type_identity<ArrayProperty<T, Traits>> = {})
{
    constexpr traits::ArrayHelperTraits<Traits> traits;
    auto& field_node = doc_helper.cur_place;
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "array";
    if constexpr (traits.min.HasValue())
    {
        field_node["min"] = traits.min.value();
    }
    if constexpr (traits.max.HasValue())
    {
        field_node["max"] = traits.max.value();
    }
    if constexpr (traits.unique_items.value_or(false))
    {
        field_node["unique_item"] = true;
    }
    auto items_node = field_node["items"];
    Append(DocHelper{doc_helper.root, items_node}, std::type_identity<T>{});
}
}  // namespace timetable_vsu_backend::openapi
