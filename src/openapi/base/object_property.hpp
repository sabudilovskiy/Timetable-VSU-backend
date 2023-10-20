#pragma once

#include <openapi/base/reflective_checks.hpp>
#include <type_traits>

#include "property_base.hpp"

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
