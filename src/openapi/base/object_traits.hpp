#pragma once

#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <type_traits>
#include <utility>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

#include "named_traits.hpp"
#include "object_property.hpp"
#include "preferences.hpp"
namespace timetable_vsu_backend::openapi
{
namespace traits
{
template <typename Traits>
struct ObjectHelperTraits : NamedHelperTraits<Traits>
{
};

}  // namespace traits
}  // namespace timetable_vsu_backend::openapi
