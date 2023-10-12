#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "models/day/postgre.hpp"
#include "models/education_type/postgre.hpp"
#include "models/lesson_type/postgre.hpp"
#include "models/lesson_v1/type.hpp"
#include "models/lesson_week_type/postgre.hpp"
#include "models/subgroup/postgre.hpp"
#include "models/timestring/postgre.hpp"
namespace models
{
using TupleLessonV1 = ::utils::convert::drop_properties_to_ref_mut_t<LessonV1>;
}
