#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <optional>
#include <type_traits>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/query.hpp>
#include <utils/convert/drop_properties_ref.hpp>
#include <utils/postgres_helper.hpp>
#include <utils/shared_transaction.hpp>

#include "models/lesson_filter/postgre.hpp"
#include "models/lesson_v1/postgre.hpp"
#include "models/lesson_v1/type.hpp"
#include "models/subgroup/serialize.hpp"
#include "sql_queries.hpp"

namespace components::controllers::postgres::lesson
{
std::vector<models::LessonV1> Controller::Search(
    const std::optional<models::LessonFilter>& filter,
    ::utils::SharedTransaction transaction) const
{
    ::utils::FillSharedTransaction(transaction,
                                                        pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qGetLessonsByFilter, filter);
    return utils::ConvertPgResultToArray<models::LessonV1>(pg_result);
}
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster())
{
}
}  // namespace components::controllers::postgres::lesson
