#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/education_type/postgre.hpp"
#include "models/teacher_filter/type.hpp"
namespace timetable_vsu_backend::models
{
using TupleTeacherFilter =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        TeacherFilter>;
}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<timetable_vsu_backend::models::TupleTeacherFilter>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.teacher_filter";
};
}  // namespace userver::storages::postgres::io
