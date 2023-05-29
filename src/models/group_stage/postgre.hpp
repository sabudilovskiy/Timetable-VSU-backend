#include <userver/storages/postgres/io/composite_types.hpp>

#include "models/education_type/postgre.hpp"
#include "models/group_stage/type.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models
{
using TupleGroupStage =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        GroupStage>;
}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io
{
template <>
struct CppToUserPg<timetable_vsu_backend::models::TupleGroupStage>
{
    static constexpr DBTypeName postgres_name = "timetable_vsu.group_stage_tuple";
};
}  // namespace userver::storages::postgres::io
