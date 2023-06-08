#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <vector>

#include "models/request_privileges/type.hpp"
#include "models/teacher/type.hpp"
#include "models/teacher_filter/type.hpp"
#include "models/teacher_info/type.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::components::controllers::postgres::teacher
{
class Controller final : public userver::components::LoggableComponentBase
{
   public:
    using userver::components::LoggableComponentBase::LoggableComponentBase;
    static constexpr inline std::string_view kName = "teacher_controller";

    Controller(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

   public:
    std::optional<boost::uuids::uuid> DropRequest(
        const boost::uuids::uuid& request_id,
        timetable_vsu_backend::utils::SharedTransaction transaction =
            nullptr) const;
    std::vector<models::RequestPrivileges> GetAllRequests(
        timetable_vsu_backend::utils::SharedTransaction transaction =
            nullptr) const;
    std::optional<boost::uuids::uuid> ApproveAndLink(
        const boost::uuids::uuid& request_id,
        const boost::uuids::uuid& teacher_id,
        timetable_vsu_backend::utils::SharedTransaction transaction =
            nullptr) const;

    std::optional<boost::uuids::uuid> ApproveAndCreateAccount(
        const boost::uuids::uuid& request_id,
        const models::TeacherInfo& teacher_info,
        timetable_vsu_backend::utils::SharedTransaction transaction =
            nullptr) const;

    std::optional<boost::uuids::uuid> Link(
        const boost::uuids::uuid& user_id, const boost::uuids::uuid& teacher_id,
        timetable_vsu_backend::utils::SharedTransaction transaction =
            nullptr) const;

    std::vector<models::Teacher> GetByFilter(
        std::optional<models::TeacherFilter>& filter,
        timetable_vsu_backend::utils::SharedTransaction transaction =
            nullptr) const;

    std::optional<boost::uuids::uuid> CreateTeacher(
        const models::TeacherInfo& teacher_info,
        timetable_vsu_backend::utils::SharedTransaction transaction =
            nullptr) const;

    timetable_vsu_backend::utils::SharedTransaction CreateTransaction();

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace
   // timetable_vsu_backend::components::controllers::postgres::teacher
