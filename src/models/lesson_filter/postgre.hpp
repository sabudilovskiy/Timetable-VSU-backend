#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/education_type/postgre.hpp"
#include "models/lesson_filter/type.hpp"
namespace models
{
using TupleLessonFilter =
    ::utils::convert::drop_properties_to_ref_const_t<LessonFilter>;
}  // namespace models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::models::TupleLessonFilter>
{
    static constexpr DBTypeName postgres_name =
        "timetable_vsu.lesson_filter_v2";
};
}  // namespace userver::storages::postgres::io
