#include "controller.hpp"

#include <fmt/core.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
#include <optional>
#include <userver/components/component_context.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/query.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/postgres_helper.hpp>
#include <utils/shared_transaction.hpp>

#include "legacy/models/substring/postgre.hpp"
#include "legacy/models/user/postgre.hpp"
#include "legacy/models/user/type.hpp"
#include "legacy/models/user_type/postgre.hpp"
#include "sql_queries.hpp"

namespace legacy::components::controllers::postgres::token
{
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster())
{
}
std::optional<legacy::models::User> Controller::GetById(
    std::string_view id, utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto result = utils::PgExecute(transaction, sql::qGetUserByTokenId, id,
                                   userver::utils::datetime::Now());
    return utils::ConvertPgResultToOptionalItem<legacy::models::User>(result);
}

std::optional<boost::uuids::uuid> Controller::CreateNew(
    const boost::uuids::uuid& user_id,
    const std::chrono::system_clock::time_point& time,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    LOG_DEBUG() << fmt::format("Try to create new token, id_user: {}",
                               boost::uuids::to_string(user_id));

    auto result = utils::PgExecute(transaction, sql::qAddToken, user_id, time);
    return utils::ConvertPgResultToOptionalItem<boost::uuids::uuid>(result);
}
}  // namespace legacy::components::controllers::postgres::token
