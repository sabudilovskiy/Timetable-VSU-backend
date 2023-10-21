#pragma once

#include <openapi/base/property_base.hpp>
#include <string>

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
