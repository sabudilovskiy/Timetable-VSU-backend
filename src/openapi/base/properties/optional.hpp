#pragma once
#include <openapi/base/property_base.hpp>
#include <optional>

namespace openapi
{
template <typename T, typename Traits = EmptyTraits>
struct OptionalProperty : public PropertyBase<std::optional<T>, Traits>
{
};

template <typename T, typename Traits>
struct types::Property<std::optional<T>, Traits>
    : public OptionalProperty<T, Traits>
{
};

}  // namespace openapi
