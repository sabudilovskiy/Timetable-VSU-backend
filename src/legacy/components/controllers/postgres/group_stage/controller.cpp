#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <optional>
#include <type_traits>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/exceptions.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/io/type_traits.hpp>
#include <userver/storages/postgres/query.hpp>
#include <utils/convert/drop_properties_ref.hpp>
#include <utils/postgres_helper.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/models/admin_account/postgre.hpp"
#include "legacy/models/admin_filter/postgre.hpp"
#include "legacy/models/group_stage/type.hpp"
#include "legacy/models/group_stage_filter/postgre.hpp"
#include "legacy/models/request_privileges/type.hpp"
#include "legacy/models/subgroup/serialize.hpp"
#include "legacy/models/substring/postgre.hpp"
#include "legacy/models/user_credentials/postgre.hpp"
#include "sql_queries.hpp"

namespace legacy::components::controllers::postgres::group_stage
{
::utils::SharedTransaction Controller::CreateTransaction()
{
    return ::utils::MakeSharedTransaction(pg_cluster_);
}
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster())
{
}

std::vector<legacy::models::GroupStage> Controller::GetByFilter(
    const std::optional<legacy::models::GroupStageFilter>& filter,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qGetGroupStages, filter);
    return utils::ConvertPgResultToArray<legacy::models::GroupStage>(pg_result);
}

}  // namespace legacy::components::controllers::postgres::group_stage
   // ::components::controllers::postgres::group_stage
