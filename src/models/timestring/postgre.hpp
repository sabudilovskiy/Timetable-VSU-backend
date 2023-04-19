#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io {
using timetable_vsu_backend::models::TimeString;
template <>
struct CppToUserPg<TimeString> {
    static constexpr DBTypeName postgres_name = "timestamptz";
};
}  // namespace userver::storages::postgres::io