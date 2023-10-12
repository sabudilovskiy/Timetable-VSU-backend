#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utility>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/teacher_info/type.hpp"
namespace models
{
using ConstTupleTeacherInfo =
    ::utils::convert::drop_properties_to_ref_const_t<TeacherInfo>;

}  // namespace models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::models::ConstTupleTeacherInfo>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.teacher_info";
};
}  // namespace userver::storages::postgres::io
