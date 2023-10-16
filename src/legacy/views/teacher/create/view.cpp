#include "view.hpp"

#include <chrono>
#include <exception>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/boost_uuid.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/parse/uuid/string.hpp>

#include "Request.hpp"
#include "Responses.hpp"
#include "legacy/components/controllers/postgres/teacher/controller.hpp"
#include "legacy/components/controllers/postgres/user/controller.hpp"
#include "http/handler_parsed.hpp"
#include "legacy/models/auth_token/serialize.hpp"
#include "legacy/models/user/serialize.hpp"
#include "legacy/models/user_type/serialize.hpp"
#include "legacy/models/user_type/type.hpp"
namespace legacy::views::teacher::create
{
namespace
{
namespace pg = legacy::components::controllers::postgres;
class Handler final
    : public http::HandlerParsed<Request, Response200, Response400, Response401,
                                 Response403>
{
   public:
    [[maybe_unused]] static constexpr std::string_view kName =
        "handler-teacher-create";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          teacher_controller(context.FindComponent<pg::teacher::Controller>()),
          user_controller(context.FindComponent<pg::user::Controller>())
    {
    }

    Response Handle(Request&& request) const override
    {
        auto user = user_controller.GetByToken(request.token());
        if (!user)
        {
            return utils::common_errors::PerformInvalidToken();
        }
        if (user->type() == legacy::models::UserType::kUser ||
            user->type() == legacy::models::UserType::kTeacher)
        {
            return utils::common_errors::PerformForbidden();
        }

        auto teacher_id =
            teacher_controller.CreateTeacher(request.teacher_info());

        if (!teacher_id)
        {
            return utils::common_errors::PerformInvalidData(
                "Can't create teacher: department_id is incorrect");
        }

        return Response200{.id_created_teacher = {teacher_id.value()}};
    }

   private:
    const pg::teacher::Controller& teacher_controller;
    const pg::user::Controller& user_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Handler>();
}

}  // namespace legacy::views::teacher::create
