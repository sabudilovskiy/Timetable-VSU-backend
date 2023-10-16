#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/admin_filter/type.hpp"
#include "legacy/models/education_type/postgre.hpp"
namespace legacy::models
{
using TupleAdminFilter =
    ::utils::convert::drop_properties_to_ref_const_t<AdminFilter>;
}  // namespace legacy::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::TupleAdminFilter>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.admin_filter_v2";
};
}  // namespace userver::storages::postgres::io
