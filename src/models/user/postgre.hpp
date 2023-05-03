#pragma once
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io {
// This specialization MUST go to the header together with the mapped type
using namespace timetable_vsu_backend::models;
template <>
struct CppToUserPg<User::Id> {
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        "uuid";
};
}  // namespace userver::storages::postgres::io
