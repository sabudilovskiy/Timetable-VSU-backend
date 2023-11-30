#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using ::legacy::models::TimeString;
template <>
struct CppToSystemPg<TimeString> : PredefinedOid<PredefinedOids::kTimestamptz>
{
};
}  // namespace userver::storages::postgres::io
