#pragma once

#include <openapi/base/named_traits.hpp>

namespace openapi::traits
{
template <auto traits>
struct UuidHelperTraits : NamedHelperTraits<traits>
{
};

}  // namespace openapi::traits
