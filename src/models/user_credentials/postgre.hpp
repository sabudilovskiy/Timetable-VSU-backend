#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/user_credentials/type.hpp"

namespace timetable_vsu_backend::models
{
using TupleUserCredentialsRaw =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        UserCredentials>;
using TupleUserCredentials = TupleUserCredentialsRaw;
}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<timetable_vsu_backend::models::TupleUserCredentials>
{
    static constexpr DBTypeName postgres_name =
        "timetable_vsu.user_credentials";
};
}  // namespace userver::storages::postgres::io
