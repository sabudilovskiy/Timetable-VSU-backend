#include "controller.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <algorithm>
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

#include "models/admin_account/postgre.hpp"
#include "models/admin_filter/postgre.hpp"
#include "models/subgroup/serialize.hpp"
#include "models/substring/postgre.hpp"
#include "models/teacher/postgre.hpp"
#include "models/teacher_filter/postgre.hpp"
#include "models/user_credentials/postgre.hpp"
#include "sql_queries.hpp"
#include "userver/storages/postgres/io/type_traits.hpp"
#include "utils/convert/drop_properties_ref.hpp"
#include "utils/postgres_helper.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::teacher {
vsu_timetable::utils::SharedTransaction Controller::CreateTransaction() {
    return vsu_timetable::utils::MakeSharedTransaction(pg_cluster_);
}
Controller::Controller(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()) {
}
std::vector<models::Teacher> Controller::GetByFilter(
    std::optional<models::TeacherFilter>& filter,
    vsu_timetable::utils::SharedTransaction transaction) const {
    vsu_timetable::utils::FillSharedTransaction(transaction, pg_cluster_);
    auto pg_result =
        utils::PgExecute(transaction, sql::qGetTeachersByFilter, filter);
    return utils::ConvertPgResultToArray<models::Teacher>(pg_result);
}

}  // namespace
   // timetable_vsu_backend::components::controllers::postgres::teacher
