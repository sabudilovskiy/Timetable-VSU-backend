#pragma once
#include <concepts>
#include <initializer_list>
#include <optional>
#include <type_traits>
#include <utility>

namespace openapi
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
    PropertyBase(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args&&...>) : value(std::forward<Args>(args)...)
    {}

    template <typename Arg>
    PropertyBase(std::initializer_list<Arg> init_list)  noexcept(std::is_nothrow_constructible_v<T, std::initializer_list<Arg>>)
        : value(std::move(init_list))
    {
    }

    auto operator<=>(const PropertyBase<value_type, Traits>& r) const = default;
    auto operator<=>(const value_type& r) const
    {
        return value <=> r;
    }

    template <class Arg>
    auto& operator=(Arg&& arg)
    {
        value = std::forward<Arg>(arg);
        return value;
    }
    auto& operator=(value_type rhs)
    {
        value = std::move(rhs);
        return *this;
    }
    value_type& operator()() noexcept
    {
        return value;
    }
    const value_type& operator()() const noexcept
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

namespace types
{
template <typename T, typename Traits = EmptyTraits>
struct Property : PropertyBase<T, Traits>
{
};

}  // namespace types

}  // namespace openapi
