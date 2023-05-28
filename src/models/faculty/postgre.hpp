#include <userver/storages/postgres/io/composite_types.hpp>

#include "models/education_type/postgre.hpp"
#include "models/faculty/type.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models
{
using TupleFaculty =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        Faculty>;
}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<timetable_vsu_backend::models::TupleFaculty>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.faculty_tuple";
};
}  // namespace userver::storages::postgres::io
