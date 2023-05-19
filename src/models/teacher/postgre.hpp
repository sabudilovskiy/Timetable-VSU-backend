#pragma once
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utility>

#include "models/teacher/type.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models {
using ConstTupleTeacher =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        Teacher>;

}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io {

template <>
struct CppToUserPg<timetable_vsu_backend::models::ConstTupleTeacher> {
    static constexpr DBTypeName postgres_name = "vsu_timetable.teacher_filter";
};
}  // namespace userver::storages::postgres::io
