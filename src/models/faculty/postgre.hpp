#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/education_type/postgre.hpp"
#include "models/faculty/type.hpp"
namespace models
{
using TupleFaculty =
    ::utils::convert::drop_properties_to_ref_const_t<
        Faculty>;
}  // namespace models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::models::TupleFaculty>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.faculty_tuple";
};
}  // namespace userver::storages::postgres::io
