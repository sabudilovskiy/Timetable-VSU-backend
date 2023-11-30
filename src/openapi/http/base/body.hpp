#pragma once

#include "body_property.hpp"

namespace openapi::http
{
template <typename T, typename... Options>
using Body = BodyProperty<T, EmptyTraits{}>;
}
