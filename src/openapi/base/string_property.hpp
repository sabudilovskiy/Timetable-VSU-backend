#pragma once

#include <string>

#include "property_base.hpp"

namespace openapi
{
template <typename Traits = EmptyTraits>
struct StringProperty : public PropertyBase<std::string, Traits>
{
};

template <typename Traits>
struct types::Property<std::string, Traits> : public StringProperty<Traits>
{
};

}  // namespace openapi
