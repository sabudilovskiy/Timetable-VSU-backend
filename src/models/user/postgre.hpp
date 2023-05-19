#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utility>

#include "models/user/type.hpp"
#include "models/user_type/postgre.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models
{
using TupleUserRaw =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<User>;

// using TupleUser =
//     userver::utils::StrongTypedef<struct TupleLessonFilterTag,
//                                   TupleUserRaw>;
using TupleUser = TupleUserRaw;
}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<timetable_vsu_backend::models::TupleUser>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.userV1";
};
}  // namespace userver::storages::postgres::io
