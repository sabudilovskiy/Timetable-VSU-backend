#pragma once

#include <openapi/to_tuple/default.hpp>
#include <optional>

namespace openapi::raw
{
template <IsDefaultToTuple T>
class ToTuple<std::optional<T>>
{
    using Type = std::optional<T>;

   public:
    using result = Type;
    static result Do(Type& t)
    {
        return t;
    }
    static result Do(const Type& t)
    {
        return t;
    }
};

template <IsNotDefaultToTuple T>
class ToTuple<std::optional<T>>
{
    using Type = std::optional<T>;
    using RawNative = to_tuple_t<T>;

   public:
    using result = std::optional<RawNative>;
    static result Do(Type& t)
    {
        if (t.has_value())
        {
            return ToTuple<T>::Do(t.value());
        }
        else
        {
            return std::nullopt;
        }
    }
    static result Do(const Type& t)
    {
        if (t.has_value())
        {
            return ToTuple<T>::Do(t.value());
        }
        else
        {
            return std::nullopt;
        }
    }
};
}  // namespace openapi::raw
