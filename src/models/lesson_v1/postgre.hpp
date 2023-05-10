#include <userver/storages/postgres/io/composite_types.hpp>

#include "models/day/postgre.hpp"
#include "models/education_type/postgre.hpp"
#include "models/lesson_type/postgre.hpp"
#include "models/lesson_v1/type.hpp"
#include "models/lesson_week_type/postgre.hpp"
#include "models/subgroup/postgre.hpp"
#include "models/timestring/postgre.hpp"
#include "utils/convert/drop_properties_ref.hpp"
namespace timetable_vsu_backend::models {
using TupleLessonV1 =
    timetable_vsu_backend::utils::convert::drop_properties_to_ref_mut_t<
        LessonV1>;
}
