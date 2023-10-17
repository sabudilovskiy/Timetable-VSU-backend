#pragma once
#include <openapi/base/uuid_property.hpp>
#include <openapi/base/uuid_traits.hpp>
#include <openapi/doc/serialize/base.hpp>

namespace openapi
{
template <typename Traits>
void Append(DocHelper doc_helper, std::type_identity<UuidProperty<Traits>> = {})
{
    constexpr traits::UuidHelperTraits<Traits> traits;
    auto& field_node = doc_helper.cur_place;
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "string";
    field_node["format"] = "uuid";
}
}  // namespace openapi
