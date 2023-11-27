#pragma once

#include <openapi/base/property_base.hpp>
#include <string>

namespace openapi
{
template <auto Traits = EmptyTraits{}>
struct StringProperty : public PropertyBase<std::string, Traits>
{
};

template <auto Traits>
struct types::Property<std::string, Traits> : public StringProperty<Traits>
{
};

}  // namespace openapi
