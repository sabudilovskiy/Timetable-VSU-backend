#include "controller.hpp"

#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <codegen/sql.hpp>
#include <openapi/postgres/mapping.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/io/uuid.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/shared_transaction.hpp>

#include "controller_fwd.hpp"
#include "models/user_credentials/postgres.hpp"

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
boost::uuids::uuid Controller::CreateNew(
    const boost::uuids::uuid& id_user,
    utils::SharedTransaction transaction) const
{
    utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result = transaction->transaction_.Execute(
        sql::add_token_to_user, id_user,
        userver::utils::datetime::Now() + std::chrono::hours(24));
    return pg_result.AsSingleRow<boost::uuids::uuid>();
}
}  // namespace controllers::token
