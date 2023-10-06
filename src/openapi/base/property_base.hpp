#pragma once
#include <concepts>
#include <initializer_list>
#include <optional>
#include <type_traits>
#include <utility>

namespace timetable_vsu_backend::openapi
{
struct EmptyTraits
{
};

template <typename T, typename Traits = EmptyTraits>
struct PropertyBase
{
    using value_type = T;
    using traits = Traits;

    template <typename... Args>
    PropertyBase(Args&&... args) : value(std::forward<Args>(args)...)
    {
    }

    template <typename Arg>
    PropertyBase(std::initializer_list<Arg> init_list)
        : value(std::move(init_list))
    {
    }

    auto operator<=>(const PropertyBase<T, Traits>& r) const = default;
    auto operator<=>(const T& r) const
    {
        return value <=> r;
    }

    template <class Arg>
    value_type& operator=(Arg&& arg)
    {
        value = std::forward<Arg>(arg);
        return value;
    }
    value_type& operator()()
    {
        return value;
    }
    const value_type& operator()() const
    {
        return value;
    }
    value_type value;
};

template <typename T>
concept IsProperty = requires
{
    typename T::traits;
    typename T::value_type;
    std::is_base_of_v<PropertyBase<typename T::traits, typename T::value_type>,
                      T>;
};

template <typename T, typename Traits = EmptyTraits>
struct Property
{
};

}  // namespace timetable_vsu_backend::openapi
