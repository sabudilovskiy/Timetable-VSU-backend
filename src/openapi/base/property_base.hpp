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

struct Yes
{
};

template <typename T, typename U>
concept HasSpaceShip = requires(T t, U u)
{
    {t <=> u};
};

template <typename T, typename U>
concept HasEquality = requires(T t, U u)
{
    {t == u};
};

template <typename T, typename U>
concept HasSpaceShipProperty = requires
{
    typename U::value_type;
    typename U::traits;
    requires HasSpaceShip<T, typename U::value_type>;
};

template <typename T, typename U>
concept HasEqualityProperty = requires
{
    typename U::value_type;
    typename U::traits;
    requires HasEquality<T, typename U::value_type>;
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

    template <typename U>
    requires HasEqualityProperty<value_type, U> auto operator==(const U& u)
    {
        return value == u();
    }

    template <typename U>
    requires HasSpaceShip<T, U> auto operator<=>(const U& u)
    {
        return value <=> u;
    }

    template <typename U>
    requires HasEquality<T, U> auto operator==(const U& u)
    {
        return value == u;
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

template <typename T, typename Traits = EmptyTraits>
struct Property
{
};

}  // namespace timetable_vsu_backend::openapi
