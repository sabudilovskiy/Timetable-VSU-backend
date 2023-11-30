#pragma once
#include <boost/uuid/uuid.hpp>
#include <optional>
#include <userver/components/loggable_component_base.hpp>
#include <userver/storages/postgres/postgres_fwd.hpp>
#include <utils/shared_transaction.hpp>
#include <vector>

#include "legacy/models/request_privileges/type.hpp"
#include "legacy/models/teacher/type.hpp"
#include "legacy/models/teacher_filter/type.hpp"
#include "legacy/models/teacher_info/type.hpp"

namespace legacy::components::controllers::postgres::teacher
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
        ::utils::SharedTransaction transaction = nullptr) const;
    std::vector<legacy::models::RequestPrivileges> GetAllRequests(
        ::utils::SharedTransaction transaction = nullptr) const;
    std::optional<boost::uuids::uuid> ApproveAndLink(
        const boost::uuids::uuid& request_id,
        const boost::uuids::uuid& teacher_id,
        ::utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> ApproveAndCreateAccount(
        const boost::uuids::uuid& request_id,
        const legacy::models::TeacherInfo& teacher_info,
        ::utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> Link(
        const boost::uuids::uuid& user_id, const boost::uuids::uuid& teacher_id,
        ::utils::SharedTransaction transaction = nullptr) const;

    std::vector<legacy::models::Teacher> GetByFilter(
        std::optional<legacy::models::TeacherFilter>& filter,
        ::utils::SharedTransaction transaction = nullptr) const;

    std::optional<boost::uuids::uuid> CreateTeacher(
        const legacy::models::TeacherInfo& teacher_info,
        ::utils::SharedTransaction transaction = nullptr) const;

    ::utils::SharedTransaction CreateTransaction();

   protected:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace legacy::components::controllers::postgres::teacher
   // ::components::controllers::postgres::teacher
