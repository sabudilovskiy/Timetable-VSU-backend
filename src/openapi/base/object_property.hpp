#pragma once

#include <openapi/base/reflective_checks.hpp>
#include <type_traits>

#include "property_base.hpp"

namespace openapi
{
template <checks::IsReflective T, typename Traits = EmptyTraits>
struct ObjectProperty : public PropertyBase<T, Traits>
{
};

template <checks::IsReflective T, typename Traits>
struct Property<T, Traits> : public ObjectProperty<T, Traits>
{
};

}  // namespace openapi
