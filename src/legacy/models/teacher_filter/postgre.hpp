#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/education_type/postgre.hpp"
#include "legacy/models/teacher_filter/type.hpp"
namespace legacy::models
{
using TupleTeacherFilter =
    ::utils::convert::drop_properties_to_ref_const_t<TeacherFilter>;
}  // namespace legacy::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::TupleTeacherFilter>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.teacher_filter";
};
}  // namespace userver::storages::postgres::io