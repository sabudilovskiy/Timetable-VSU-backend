#pragma once

#include <stdexcept>
#include <unordered_map>
#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>

#include "openapi/base/array_property.hpp"
#include "openapi/base/array_traits.hpp"
#include "openapi/base/named_traits.hpp"
#include "utils/constexpr_string.hpp"

namespace userver::formats::parse
{
template <typename T, typename Traits>
timetable_vsu_backend::openapi::ArrayProperty<T, Traits> Parse(
    const json::Value& item,
    To<timetable_vsu_backend::openapi::ArrayProperty<T, Traits>>)
{
    using namespace timetable_vsu_backend::openapi;

    constexpr traits::ArrayHelperTraits<Traits> traits;

    std::vector<T> result = item.As<std::vector<T>>();

    if constexpr (traits.min.HasValue())
    {
        if (result.size() < traits.min.value())
        {
            throw std::runtime_error(
                fmt::format("Field has elements less than "
                            "allowed, current: {}, min: {}",
                            result.size(), traits.min.value()));
        }
    }
    if constexpr (traits.max.HasValue())
    {
        if (result.size() > traits.max.value())
        {
            throw std::runtime_error(
                fmt::format("Field has elements more than "
                            "allowed, current: {}, max: {}",
                            result.size(), traits.max.value()));
        }
    }
    if constexpr (traits.unique_items.value_or(false))
    {
        std::unordered_map<T, size_t> map;
        size_t index = 0;
        for (auto& elem : result)
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
    return {std::move(result)};
}

}  // namespace userver::formats::parse
