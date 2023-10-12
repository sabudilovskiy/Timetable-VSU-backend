#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/education_type/postgre.hpp"
#include "models/group_stage/type.hpp"
namespace models
{
using TupleGroupStage =
    ::utils::convert::drop_properties_to_ref_const_t<GroupStage>;
}  // namespace models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::models::TupleGroupStage>
{
    static constexpr DBTypeName postgres_name =
        "timetable_vsu.group_stage_tuple";
};
}  // namespace userver::storages::postgres::io
