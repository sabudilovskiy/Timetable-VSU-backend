#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utility>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/teacher_info/type.hpp"
namespace legacy::models
{
using ConstTupleTeacherInfo =
    ::utils::convert::drop_properties_to_ref_const_t<TeacherInfo>;

}  // namespace legacy::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::ConstTupleTeacherInfo>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.teacher_info";
};
}  // namespace userver::storages::postgres::io
