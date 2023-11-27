#pragma once
#include <boost/uuid/uuid.hpp>
#include <compare>
#include <initializer_list>
#include <openapi/base/property_base.hpp>
#include <type_traits>

namespace openapi
{
template <auto Traits>
struct PropertyBase<boost::uuids::uuid, Traits>
{
    using T = boost::uuids::uuid;
    using value_type = T;
    static constexpr auto traits = Traits;

    template <typename... Args>
    PropertyBase(Args&&... args) noexcept(
        std::is_nothrow_constructible_v<T, Args&&...>)
        : value(std::forward<Args>(args)...)
    {
    }

    template <typename Arg>
    PropertyBase(std::initializer_list<Arg> init_list) noexcept(
        std::is_nothrow_constructible_v<T, std::initializer_list<Arg>>)
        : value(std::move(init_list))
    {
    }

    std::partial_ordering operator<=>(
        const PropertyBase<value_type, Traits>& r) const noexcept
    {
        return *this <=> r();
    }
    std::partial_ordering operator<=>(const value_type& r) const noexcept
    {
        if (value == r)
        {
            return std::partial_ordering::equivalent;
        }
        else
            return std::partial_ordering::unordered;
    }

    bool operator==(const PropertyBase<value_type, Traits>& r) const = default;

    template <class Arg>
    value_type& operator=(Arg&& arg) noexcept(
        std::is_nothrow_assignable_v<boost::uuids::uuid, Arg>)
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

template <auto traits>
struct UuidProperty : PropertyBase<boost::uuids::uuid, traits>
{
};

template <auto traits>
struct types::Property<boost::uuids::uuid, traits> : UuidProperty<traits>
{
};
}  // namespace openapi
