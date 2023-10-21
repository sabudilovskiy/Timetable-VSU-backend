#pragma once

#include <openapi/base/properties/datetime.hpp>
#include "openapi/doc/base.hpp"

namespace openapi
{
template <typename Traits>
void Append(DocHelper doc_helper, std::type_identity<DateTimeProperty<Traits>> = {})
{
    auto& field_node = doc_helper.cur_place;
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "string";
    field_node["format"] = "datetime";
}
}  // namespace openapi
