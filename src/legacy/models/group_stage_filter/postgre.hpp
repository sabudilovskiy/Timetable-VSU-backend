#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/education_type/postgre.hpp"
#include "legacy/models/group_stage_filter/type.hpp"
namespace legacy::models
{
using TupleGroupStageFilter =
    ::utils::convert::drop_properties_to_ref_const_t<GroupStageFilter>;
}  // namespace legacy::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<::legacy::models::TupleGroupStageFilter>
{
    static constexpr DBTypeName postgres_name =
        "timetable_vsu.group_stage_filter";
};
}  // namespace userver::storages::postgres::io
