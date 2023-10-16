#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/user_credentials/type.hpp"

namespace legacy::models
{
using TupleUserCredentialsRaw =
    ::utils::convert::drop_properties_to_ref_const_t<UserCredentials>;
using TupleUserCredentials = TupleUserCredentialsRaw;
}  // namespace legacy::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::TupleUserCredentials>
{
    static constexpr DBTypeName postgres_name =
        "timetable_vsu.user_credentials";
};
}  // namespace userver::storages::postgres::io
