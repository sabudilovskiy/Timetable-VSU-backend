#include <userver/storages/postgres/io/composite_types.hpp>
#include <utils/convert/drop_properties_ref.hpp>

#include "legacy/models/day/postgre.hpp"
#include "legacy/models/education_type/postgre.hpp"
#include "legacy/models/lesson_type/postgre.hpp"
#include "legacy/models/lesson_v1/type.hpp"
#include "legacy/models/lesson_week_type/postgre.hpp"
#include "legacy/models/subgroup/postgre.hpp"
#include "legacy/models/timestring/postgre.hpp"
namespace legacy::models
{
using TupleLessonV1 = ::utils::convert::drop_properties_to_ref_mut_t<LessonV1>;
}
