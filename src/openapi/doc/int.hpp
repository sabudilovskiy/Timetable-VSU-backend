#pragma once
#include <openapi/doc/base.hpp>

namespace openapi
{
inline void Append(DocHelper doc_helper, std::type_identity<std::int32_t>)
{
    auto& cur = doc_helper.cur_place;
    if (cur.IsObject())
    {
        cur = userver::formats::yaml::Type::kObject;
    }
    cur["type"] = "integer";
    cur["format"] = "int32";
}
}  // namespace openapi
