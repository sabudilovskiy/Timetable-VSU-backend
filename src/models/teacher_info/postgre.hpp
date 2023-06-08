#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utility>

#include "models/teacher_info/type.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models
{
using ConstTupleTeacherInfo =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        TeacherInfo>;

}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<timetable_vsu_backend::models::ConstTupleTeacherInfo>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.teacher_info";
};
}  // namespace userver::storages::postgres::io
