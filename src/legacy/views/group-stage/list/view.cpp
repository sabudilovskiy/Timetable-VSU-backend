#include "view.hpp"

#include <chrono>
#include <exception>
#include <openapi/json/parse/enum.hpp>
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
#include "legacy/components/controllers/postgres/group_stage/controller.hpp"
#include "legacy/models/auth_token/serialize.hpp"
#include "legacy/models/education_type/all.hpp"
#include "legacy/models/substring/parse.hpp"
#include "legacy/models/user/serialize.hpp"
namespace legacy::views::group::stage::list
{
namespace
{
namespace pg = legacy::components::controllers::postgres;
class Handler final : public http::HandlerParsed<Request, Response200>
{
   public:
    [[maybe_unused]] static constexpr std::string_view kName =
        "handler-group-stage-list";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          group_stage_controller(
              context.FindComponent<pg::group_stage::Controller>())
    {
    }

    Response Handle(Request&& request) const override
    {
        auto group_stages =
            group_stage_controller.GetByFilter(request.filter());
        Response200 resp;
        resp.group_stages() = std::move(group_stages);
        return resp;
    }

   private:
    const pg::group_stage::Controller& group_stage_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Handler>();
}

}  // namespace legacy::views::group::stage::list
