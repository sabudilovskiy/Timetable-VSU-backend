#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <vector>

#include "models/faculty/type.hpp"
#include "models/faculty_filter/type.hpp"
#include "models/request_privileges/type.hpp"
#include "models/teacher/type.hpp"
#include "models/teacher_filter/type.hpp"
#include "models/teacher_info/type.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::faculty
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "faculty_controller";

    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

    std::vector<models::Faculty> GetByFilter(
        const std::optional<models::FacultyFilter>& filter,
        utils::SharedTransaction transaction = nullptr) const;

   public:
    timetable_vsu_backend::utils::SharedTransaction CreateTransaction();

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace
   // timetable_vsu_backend::components::controllers::postgres::faculty
