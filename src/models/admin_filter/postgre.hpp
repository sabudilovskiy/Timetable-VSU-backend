#include <userver/storages/postgres/io/composite_types.hpp>

#include "models/admin_filter/type.hpp"
#include "models/education_type/postgre.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models {
using TupleAdminFilter =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        AdminFilter>;
}  // namespace timetable_vsu_backend::models

namespace userver::storages::postgres::io {

template <>
struct CppToUserPg<timetable_vsu_backend::models::TupleAdminFilter> {
    static constexpr DBTypeName postgres_name = "vsu_timetable.admin_filter_v2";
};
}  // namespace userver::storages::postgres::io
