#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/education_type/postgre.hpp"
#include "legacy/models/group_stage/type.hpp"
namespace legacy::models
{
using TupleGroupStage =
    ::utils::convert::drop_properties_to_ref_const_t<GroupStage>;
}  // namespace legacy::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::TupleGroupStage>
{
    static constexpr DBTypeName postgres_name =
        "timetable_vsu.group_stage_tuple";
};
}  // namespace userver::storages::postgres::io
