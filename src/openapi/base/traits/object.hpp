#pragma once

#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/object.hpp>
#include <type_traits>
#include <utility>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
namespace traits
{
template <auto traits>
struct ObjectHelperTraits : NamedHelperTraits<traits>
{
};

}  // namespace traits
}  // namespace openapi
