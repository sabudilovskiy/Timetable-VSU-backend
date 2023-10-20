#pragma once

#include <optional>
#include <vector>

#include "property_base.hpp"

namespace openapi
{
template <typename T, typename Traits = EmptyTraits>
struct ArrayProperty : public PropertyBase<std::vector<T>, Traits>
{
};

template <typename T, typename Traits>
struct types::Property<std::vector<T>, Traits> : public ArrayProperty<T, Traits>
{
};

}  // namespace openapi
