#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/storages/postgres/io/uuid.hpp>
#include <utility>

#include "models/admin_account/type.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models {
using AdminAccountTuple =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_mut_t<
        AdminAccount>;
}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io {

template <>
struct CppToUserPg<timetable_vsu_backend::models::AdminAccountTuple> {
    static constexpr DBTypeName postgres_name = "vsu_timetable.admin_account";
};
}  // namespace userver::storages::postgres::io
