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
#include "http/handler_parsed.hpp"
#include "legacy/components/controllers/postgres/admin/controller.hpp"
#include "legacy/components/controllers/postgres/user/controller.hpp"
#include "legacy/models/auth_token/serialize.hpp"
#include "legacy/models/user/serialize.hpp"
#include "legacy/models/user_type/serialize.hpp"
namespace legacy::views::admin::list
{
static_assert(userver::formats::common::impl::kHasSerialize<
              userver::formats::json::Value, ::legacy::models::User>);
namespace
{
namespace pg = legacy::components::controllers::postgres;
class Handler final
    : public http::HandlerParsed<Request, Response200, Response400, Response401,
                                 Response403>
{
   public:
    [[maybe_unused]] static constexpr std::string_view kName =
        "handler-admin-list";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          user_controller(context.FindComponent<pg::user::Controller>()),
          admin_controller(context.FindComponent<pg::admin::Controller>())
    {
    }

    Response Handle(Request&& request) const override
    {
        auto user = user_controller.GetByToken(request.token());
        if (!user)
        {
            return utils::common_errors::PerformInvalidToken();
        }
        if (user->type() != legacy::models::UserType::kRoot)
        {
            return utils::common_errors::PerformForbidden();
        }
        auto admins = admin_controller.GetByFilter(request.filter());
        Response200 resp;
        resp.admins() = std::move(admins);
        return resp;
    }

   private:
    const pg::user::Controller& user_controller;
    const pg::admin::Controller& admin_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Handler>();
}

}  // namespace legacy::views::admin::list
