#pragma once

#include <openapi/base/named_traits.hpp>

namespace openapi::traits
{
template <typename Traits>
struct UuidHelperTraits : NamedHelperTraits<Traits>
{
};

}  // namespace openapi::traits
