#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using ::models::SubString;
template <>
struct CppToSystemPg<SubString> : PredefinedOid<PredefinedOids::kText>
{
};
}  // namespace userver::storages::postgres::io
