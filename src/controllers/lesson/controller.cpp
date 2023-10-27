#include "controller.hpp"

#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <codegen/sql.hpp>
#include <cstdint>
#include <models/lesson_filter/postgres.hpp>
#include <openapi/postgres/mapping.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/io/array_types.hpp>
#include <userver/storages/postgres/io/integral_types.hpp>
#include <userver/storages/postgres/io/optional.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/storages/postgres/io/type_traits.hpp>
#include <userver/storages/postgres/io/uuid.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/shared_transaction.hpp>

#include "controller_fwd.hpp"
#include "legacy/models/day/postgre.hpp"
#include "legacy/models/education_type/postgre.hpp"
#include "legacy/models/lesson_type/postgre.hpp"
#include "legacy/models/lesson_week_type/postgre.hpp"
#include "legacy/models/subgroup/postgre.hpp"
#include "models/user_credentials/postgres.hpp"
#include "legacy/models/substring/postgre.hpp"

namespace controllers::lesson
{
void Append(userver::components::ComponentList& list)
{
    list.Append<Controller>();
}
Controller::Controller(const userver::components::ComponentConfig& cfg,
                       const userver::components::ComponentContext& ctx)
    : Base(cfg, ctx)
{
}
std::vector<models::LessonV1> Controller::FindLessons(
    const std::optional<models::LessonFilter>& filter,
    utils::SharedTransaction transaction) const
{
    FillTransaction(transaction);
    return transaction->Execute_R<std::vector<models::LessonV1>>(
        sql::get_lessons_by_filter, filter);
}
}  // namespace controllers::lesson
