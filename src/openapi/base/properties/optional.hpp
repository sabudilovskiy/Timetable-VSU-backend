#pragma once
#include <compare>
#include <openapi/base/property_base.hpp>
#include <optional>

namespace openapi
{
template <typename T, auto Traits>
struct PropertyBase<std::optional<T>, Traits>
{
    using value_type = std::optional<T>;
    static constexpr auto traits = Traits;

    template <typename... Args>
    PropertyBase(Args&&... args) noexcept(
        std::is_nothrow_constructible_v<value_type, Args&&...>)
        : value(std::forward<Args>(args)...)
    {
    }

    template <typename Arg>
    PropertyBase(std::initializer_list<Arg> init_list) noexcept(
        std::is_nothrow_constructible_v<value_type, std::initializer_list<Arg>>)
        : value(std::move(init_list))
    {
    }

    auto operator<=>(const PropertyBase<value_type, Traits>& r) const
    {
        return *this <=> r.value;
    }
    std::partial_ordering operator<=>(const value_type& r) const
    {
        if (value.has_value() && r.has_value())
        {
            return value.value() <=> r.value();
        }
        else
            return std::partial_ordering::unordered;
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

template <typename T, auto Traits = EmptyTraits{}>
struct OptionalProperty : public PropertyBase<std::optional<T>, Traits>
{
};

template <typename T, auto Traits>
struct types::Property<std::optional<T>, Traits>
    : public OptionalProperty<T, Traits>
{
};

}  // namespace openapi
