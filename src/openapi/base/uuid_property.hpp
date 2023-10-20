#pragma once
#include <boost/uuid/uuid.hpp>
#include <compare>
#include <openapi/base/property_base.hpp>

namespace openapi
{
template <typename Traits>
struct PropertyBase<boost::uuids::uuid, Traits>
{
    using value_type = boost::uuids::uuid;
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

    std::partial_ordering operator<=>(
        const PropertyBase<value_type, Traits>& r) const
    {
        return *this <=> r();
    }
    std::partial_ordering operator<=>(const value_type& r) const
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

template <typename Traits>
struct UuidProperty : PropertyBase<boost::uuids::uuid, Traits>
{
};

template <typename Traits>
struct types::Property<boost::uuids::uuid, Traits> : UuidProperty<Traits>
{
};
}  // namespace openapi
