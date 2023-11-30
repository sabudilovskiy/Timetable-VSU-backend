#pragma once

#include <openapi/as_tuple/default.hpp>
#include <optional>

namespace openapi::raw
{
template <IsDefaultAsTuple T>
class AsTuple<std::optional<T>>
{
    using Type = std::optional<T>;
    using RawMutNative = typename AsTuple<T>::result_mut;
    using RawConstNative = typename AsTuple<T>::result_const;

   public:
    using result_mut = std::optional<T>&;
    using result_const = const std::optional<T>&;
    static result_mut Do(Type& t)
    {
        return t;
    }
    static result_const Do(const Type& t)
    {
        return t;
    }
};

template <IsNotDefaultAsTuple T>
class AsTuple<std::optional<T>>
{
    using Type = std::optional<T>;
    using Native = typename T::value_type;
    using RawMutNative = typename AsTuple<Native>::result_mut;
    using RawConstNative = typename AsTuple<Native>::result_const;

   public:
    using result_mut = std::optional<RawMutNative>;
    using result_const = std::optional<RawMutNative>;
    static result_mut Do(Type& t)
    {
        if (t.has_value())
        {
            return AsTuple<T>::Do(t.value());
        }
        else
        {
            return std::nullopt;
        }
    }
    static result_const Do(const Type& t)
    {
        if (t.has_value())
        {
            return AsTuple<T>::Do(t.value());
        }
        else
        {
            return std::nullopt;
        }
    }
};
}  // namespace openapi::raw
