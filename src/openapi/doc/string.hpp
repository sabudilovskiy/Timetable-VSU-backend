#pragma once
#include <openapi/doc/base.hpp>

namespace openapi
{
inline void Append(DocHelper doc_helper, std::type_identity<std::string>)
{
    auto& cur = doc_helper.cur_place;
    if (cur.IsObject())
    {
        cur = userver::formats::yaml::Type::kObject;
    }
    cur["type"] = "string";
}

template <typename Traits>
void Append(DocHelper doc_helper,
            std::type_identity<StringProperty<Traits>> = {})
{
    constexpr traits::StringHelperTraits<Traits> traits;
    auto& field_node = doc_helper.cur_place;
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "string";
    if constexpr (!traits.pattern.empty())
    {
        field_node["pattern"] = std::string{traits.pattern.AsStringView()};
    }
}
}  // namespace openapi
