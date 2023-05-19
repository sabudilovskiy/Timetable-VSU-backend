#include "view.hpp"

#include <chrono>
#include <exception>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>

#include "Request.hpp"
#include "Responses.hpp"
#include "components/controllers/postgres/admin/controller.hpp"
#include "components/controllers/postgres/user/controller.hpp"
#include "http/handler_parsed.hpp"
#include "models/auth_token/serialize.hpp"
#include "models/user/serialize.hpp"
#include "models/user_type/serialize.hpp"
#include "utils/parse/uuid/string.hpp"
namespace timetable_vsu_backend::views::admin::create
{
static_assert(
    userver::formats::common::impl::kHasSerialize<
        userver::formats::json::Value, timetable_vsu_backend::models::User>);
namespace
{
namespace pg = components::controllers::postgres;
class Handler final
    : public http::HandlerParsed<Request, Response200, Response400, Response401,
                                 Response403>
{
    static Response400 PerformLoginTaken()
    {
        Response400 resp;
        resp.description = "Account can't created: login is already taken";
        resp.machine_id = "LOGIN_TAKEN";
        return resp;
    }
    static Response401 PerformInvalidToken()
    {
        Response401 resp;
        resp.description = "Account not founded: token invalid";
        resp.machine_id = "INVALID_TOKEN";
        return resp;
    }
    static Response403 PerformForbidden()
    {
        Response403 resp;
        resp.description = "Not enough permissions to do so";
        resp.machine_id = "NOT_ENOUGH_PERMISSIONS";
        return resp;
    }

   public:
    [[maybe_unused]] static constexpr std::string_view kName =
        "handler-admin-create";
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
            return PerformInvalidToken();
        }
        if (user->type() != models::UserType::kRoot)
        {
            return PerformForbidden();
        }
        auto admin = admin_controller.CreateAdmin(request.credentials());
        if (!admin)
        {
            return PerformLoginTaken();
        }
        Response200 resp;
        resp.created_account() = std::move(admin.value());
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

}  // namespace timetable_vsu_backend::views::admin::create
