#pragma once

#include <openapi/base/property_base.hpp>
#include <optional>
#include <vector>

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
