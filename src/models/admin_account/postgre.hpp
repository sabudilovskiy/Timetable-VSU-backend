#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <models/admin_account/type.hpp>
#include "userver/storages/postgres/io/pg_types.hpp"

namespace userver::storages::postgres::io{
    template <>
    struct CppToPg<models::AdminAccount>{
        static constexpr DBTypeName postgres_name = "timetable_vsu.admin_account";
    };
}