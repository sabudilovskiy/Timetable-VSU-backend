#pragma once
#include <fmt/core.h>
#include <limits>
#include <openapi/doc/base.hpp>
#include <type_traits>

namespace openapi
{
inline void Append(
    DocHelper doc_helper, std::type_identity<std::int32_t>)
{
    auto& cur = doc_helper.cur_place;
    if (cur.IsObject())
    {
        cur = userver::formats::yaml::Type::kObject;
    }
    cur["type"] = "integer";
    cur["format"] = "int32";
}

template <typename Integer>
requires std::is_integral_v<Integer> inline void Append(
    DocHelper doc_helper, std::type_identity<Integer>)
{
    auto& cur = doc_helper.cur_place;
    if (cur.IsObject())
    {
        cur = userver::formats::yaml::Type::kObject;
    }
    cur["type"] = "integer";
    cur["minimum"] = std::numeric_limits<Integer>::min();
    cur["maximum"] = std::numeric_limits<Integer>::max();
}
}  // namespace openapi
