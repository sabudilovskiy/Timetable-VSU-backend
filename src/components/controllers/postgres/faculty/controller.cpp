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

#include "models/admin_account/postgre.hpp"
#include "models/admin_filter/postgre.hpp"
#include "models/faculty/type.hpp"
#include "models/faculty_filter/postgre.hpp"
#include "models/request_privileges/type.hpp"
#include "models/subgroup/serialize.hpp"
#include "models/substring/postgre.hpp"
#include "models/user_credentials/postgre.hpp"
#include "sql_queries.hpp"

namespace components::controllers::postgres::faculty
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

std::vector<models::Faculty> Controller::GetByFilter(
    const std::optional<models::FacultyFilter>& filter,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qGetFacultiesByFilter, filter);
    return utils::ConvertPgResultToArray<models::Faculty>(pg_result);
}

}  // namespace
   // ::components::controllers::postgres::faculty
