#pragma once

#include <cstddef>
#include <openapi/http/base/response_property.hpp>
#include <openapi/http/base/response_traits.hpp>

namespace timetable_vsu_backend::openapi::http
{
template <typename T, std::size_t Code>
using Response = ResponseProperty<T, ResponseTraits<Code>>;
}
