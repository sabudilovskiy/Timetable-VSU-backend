#pragma once

#include <cstddef>
#include <openapi/base/object_property.hpp>
#include <openapi/http/base/response_property.hpp>
#include <openapi/http/base/response_traits.hpp>

namespace timetable_vsu_backend::openapi::http
{
template <checks::IsReflective T, std::size_t Code>
using Resp = ResponseProperty<T, ResponseTraits<Code>>;
}
