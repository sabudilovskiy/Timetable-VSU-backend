#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/storages/postgres/io/uuid.hpp>
#include <utility>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/admin_account/type.hpp"
namespace models
{
using AdminAccountTuple =
    ::utils::convert::drop_properties_to_ref_mut_t<AdminAccount>;
}  // namespace models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::models::AdminAccountTuple>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.admin_account";
};
}  // namespace userver::storages::postgres::io
