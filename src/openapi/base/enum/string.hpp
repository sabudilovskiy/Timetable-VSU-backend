#pragma once
#include <openapi/base/enum/introspector.hpp>
#include <optional>
#include <string_view>

namespace openapi
{
template <typename T>
requires HasIntrospector<T> constexpr std::string_view to_string_view(
    const T& t)
{
    std::size_t index = 0;
    for (auto val : enum_introspector<T>::values)
    {
        if (t == val)
        {
            break;
        }
        index++;
    }
    return enum_introspector<T>::names[index];
}

template <typename T>
requires HasIntrospector<T> constexpr std::optional<T> from_string_view(
    std::string_view sv)
{
    constexpr auto names = enum_introspector<T>::names;
    constexpr auto values = enum_introspector<T>::values;
    std::size_t index = 0;
    for (auto name : names)
    {
        if (sv == name)
        {
            break;
        }
        index++;
    }
    if (index == names.size())
        return std::nullopt;
    else
        return values[index];
}
}  // namespace openapi
