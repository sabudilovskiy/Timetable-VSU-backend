#pragma once

#include <openapi/base/array_property.hpp>
#include <openapi/base/array_traits.hpp>
#include <openapi/base/named_traits.hpp>
#include <stdexcept>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/formats/serialize/to.hpp>
#include <userver/logging/log.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
template <typename T, typename Traits>
userver::formats::json::Value Serialize(
    const ArrayProperty<T, Traits>& item,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    constexpr traits::ArrayHelperTraits<Traits> traits;

    userver::formats::json::ValueBuilder result{
        userver::formats::json::Type::kArray};

    auto& serialized_value = item();

    if constexpr (traits.min.HasValue())
    {
        if (serialized_value.size() < *traits.min)
        {
            throw std::runtime_error(
                fmt::format("Field has elements less than "
                            "allowed, current: {}, min: {}",
                            serialized_value.size(), *traits.min));
        }
    }
    if constexpr (traits.max.HasValue())
    {
        if (serialized_value.size() > *traits.max)
        {
            throw std::runtime_error(
                fmt::format("Field has elements more than "
                            "allowed, current: {}, max: {}",
                            serialized_value.size(), *traits.max));
        }
    }
    if constexpr (traits.unique_items.value_or(false))
    {
        std::unordered_map<T, size_t> map;
        size_t index = 0;
        for (auto& elem : serialized_value)
        {
            auto [it, inserted] = map.try_emplace(elem, index);
            if (!inserted)
            {
                throw std::runtime_error(
                    fmt::format("Field has equals elements, "
                                "element {} and {} are equal",
                                it->second + 1, index + 1));
            }
            index++;
        }
    }
    for (auto& elem : serialized_value)
    {
        result.PushBack(elem);
    }
    return result.ExtractValue();
}
}  // namespace openapi
