#pragma once

#include <boost/uuid/uuid.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <utils/component_list_fwd.hpp>
#include <utils/pg_controller.hpp>
#include <utils/shared_transaction.hpp>

namespace controllers::lesson
{
using Base = utils::PgController<"new-lesson-controller", "postgres-db-1">;
struct Controller : Base
{
    Controller(const userver::components::ComponentConfig& cfg,
               const userver::components::ComponentContext& ctx);
    boost::uuids::uuid CreateNew(
        const boost::uuids::uuid& id_user,
        utils::SharedTransaction transaction = nullptr) const;
};
}  // namespace controllers::token
