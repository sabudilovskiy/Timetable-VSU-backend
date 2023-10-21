#pragma once
#include <boost/uuid/uuid.hpp>
#include <openapi/base/reflective/checks.hpp>

namespace openapi
{
template <>
constexpr inline bool checks::is_reflective_v<boost::uuids::uuid> = false;
}