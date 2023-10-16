#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/education_type/postgre.hpp"
#include "legacy/models/faculty/type.hpp"
namespace legacy::models
{
using TupleFaculty = ::utils::convert::drop_properties_to_ref_const_t<Faculty>;
}  // namespace legacy::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::TupleFaculty>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.faculty_tuple";
};
}  // namespace userver::storages::postgres::io
