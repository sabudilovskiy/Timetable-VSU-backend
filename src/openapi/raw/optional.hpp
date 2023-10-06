#pragma once

#include <openapi/raw/default.hpp>
#include <optional>

namespace timetable_vsu_backend::openapi::raw
{
template <IsDefault T>
class Raw<std::optional<T>>
{
    using Type = std::optional<T>;
    using Native = typename T::value_type;
    using RawMutNative = typename Raw<Native>::result_mut;
    using RawConstNative = typename Raw<Native>::result_const;

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

template <IsNotDefault T>
class Raw<std::optional<T>>
{
    using Type = std::optional<T>;
    using Native = typename T::value_type;
    using RawMutNative = typename Raw<Native>::result_mut;
    using RawConstNative = typename Raw<Native>::result_const;

   public:
    using result_mut = std::optional<RawMutNative>;
    using result_const = std::optional<RawMutNative>;
    static result_mut Do(Type& t)
    {
        if (t.has_value())
        {
            return Raw<T>::Do(t.value());
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
            return Raw<T>::Do(t.value());
        }
        else
        {
            return std::nullopt;
        }
    }
};
}  // namespace timetable_vsu_backend::openapi::raw
