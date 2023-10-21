#pragma once

#include <openapi/base/property_base.hpp>
#include <openapi/base/reflective/checks.hpp>
#include <type_traits>

namespace openapi
{
template <typename T, typename Traits = EmptyTraits>
requires checks::is_reflective_v<T> struct ObjectProperty
    : public PropertyBase<T, Traits>
{
};

template <typename T, typename Traits>
requires checks::is_reflective_v<T> struct types::Property<T, Traits>
    : public ObjectProperty<T, Traits>
{
};

}  // namespace openapi
