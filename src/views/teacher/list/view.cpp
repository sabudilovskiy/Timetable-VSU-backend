#include "view.hpp"

#include <chrono>
#include <exception>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/boost_uuid.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>

#include "Request.hpp"
#include "Responses.hpp"
#include "components/controllers/postgres/teacher/controller.hpp"
#include "http/handler_parsed.hpp"
#include "models/auth_token/serialize.hpp"
#include "models/user/serialize.hpp"
#include "models/user_type/serialize.hpp"
#include "utils/parse/uuid/string.hpp"
namespace timetable_vsu_backend::views::teacher::list
{
namespace
{
namespace pg = components::controllers::postgres;
class Handler final : public http::HandlerParsed<Request, Response200>
{
   public:
    [[maybe_unused]] static constexpr std::string_view kName =
        "handler-teacher-list";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          teacher_controller(context.FindComponent<pg::teacher::Controller>())
    {
    }

    Response Handle(Request&& request) const override
    {
        auto teachers = teacher_controller.GetByFilter(request.filter());
        Response200 resp;
        resp.teachers() = std::move(teachers);
        return resp;
    }

   private:
    const pg::teacher::Controller& teacher_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Handler>();
}

}  // namespace timetable_vsu_backend::views::teacher::list
