#pragma once
#include <openapi/base/properties/uuid.hpp>
#include <openapi/base/traits/uuid.hpp>
#include <openapi/doc/base.hpp>

namespace openapi
{
template <auto Traits>
void Append(DocHelper doc_helper, std::type_identity<UuidProperty<Traits>> = {})
{
    auto& field_node = doc_helper.cur_place;
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "string";
    field_node["format"] = "uuid";
}
}  // namespace openapi
