#include <userver/storages/postgres/io/composite_types.hpp>

#include "models/lesson_filter/type.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models {
using TupleLessonFilter =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_const_t<
        LessonFilter>;
}
namespace userver::storages::postgres::io {

template <>
struct CppToUserPg<timetable_vsu_backend::models::TupleLessonFilter> {
    static constexpr DBTypeName postgres_name = "vsu_timetable.lesson_filter";
};
}  // namespace userver::storages::postgres::io