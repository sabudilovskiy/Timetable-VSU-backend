#include "view.hpp"

#include <chrono>
#include <exception>
#include <openapi/json/serialize/enum.hpp>
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
#include "http/handler_parsed.hpp"
#include "legacy/components/controllers/postgres/faculty/controller.hpp"
#include "legacy/models/auth_token/serialize.hpp"
#include "legacy/models/user/serialize.hpp"
namespace legacy::views::faculty::list
{
namespace
{
namespace pg = legacy::components::controllers::postgres;
class Handler final : public http::HandlerParsed<Request, Response200>
{
   public:
    [[maybe_unused]] static constexpr std::string_view kName =
        "handler-faculty-list";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          faculty_controller(context.FindComponent<pg::faculty::Controller>())
    {
    }

    Response Handle(Request&& request) const override
    {
        auto faculties = faculty_controller.GetByFilter(request.filter());
        Response200 resp;
        resp.faculties() = std::move(faculties);
        return resp;
    }

   private:
    const pg::faculty::Controller& faculty_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Handler>();
}

}  // namespace legacy::views::faculty::list
