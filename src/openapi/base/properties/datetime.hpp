#pragma once
#include <chrono>
#include <compare>
#include <openapi/base/property_base.hpp>
#include <userver/storages/postgres/io/chrono.hpp>

namespace openapi
{
template <typename Traits>
struct PropertyBase<userver::storages::postgres::TimePointTz, Traits>
{
    using T = userver::storages::postgres::TimePointTz;
    using value_type = T;
    using traits = Traits;

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

    auto operator<=>(const PropertyBase<value_type, Traits>& r) const
    {
        return *this <=> r.value;
    }
    auto operator<=>(const value_type& r) const
    {
        return value.GetUnderlying() <=> r.GetUnderlying();
    }

    bool operator==(const PropertyBase<value_type, Traits>& r) const
    {
        return value.GetUnderlying() == r.value.GetUnderlying();
    }
    bool operator==(const value_type& r) const
    {
        return value.GetUnderlying() == r.GetUnderlying();
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

template <typename Traits>
struct DateTimeProperty
    : PropertyBase<userver::storages::postgres::TimePointTz, Traits>
{
};

template <typename Traits>
struct types::Property<userver::storages::postgres::TimePointTz, Traits>
    : DateTimeProperty<Traits>
{
};
}  // namespace openapi
