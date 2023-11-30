#pragma once
#include <userver/storages/postgres/component.hpp>
#include <utils/component.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/shared_transaction.hpp>
namespace utils
{
template <ConstexprString Name, ConstexprString BdName>
struct PgController : Component<Name>
{
    PgController(const userver::components::ComponentConfig& cfg,
                 const userver::components::ComponentContext& ctx)
        : Component<Name>(cfg, ctx),
          pg_cluster_(ctx.FindComponent<userver::components::Postgres>(
                             BdName.AsStringView())
                          .GetCluster())
    {
    }
    utils::SharedTransaction CreateTransaction(
        SafeTranscaction::ActionOnDeath action_on_death =
            SafeTranscaction::ActionOnDeath::kCommit) const
    {
        return MakeSharedTransaction(pg_cluster_, action_on_death);
    }
    void FillTransaction(utils::SharedTransaction& tr,
                         SafeTranscaction::ActionOnDeath action_on_death =
                             SafeTranscaction::ActionOnDeath::kCommit) const
    {
        FillSharedTransaction(tr, pg_cluster_, action_on_death);
    }

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace utils
