#include "view.hpp"

#include <chrono>
#include <exception>
#include <openapi/all.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>

#include "controllers/token/controller.hpp"
#include "controllers/user/controller.hpp"
#include "declarations.hpp"
#include "models/error_v1/type.hpp"

namespace views::login
{
namespace
{
using Resp200 = Resp<Response, 200>;
using Resp401 = Resp<models::ResponseErrorV1, 401>;
using Base =
    openapi::http::OpenApiHandler<"login-view", Request, Resp200, Resp401>;
struct View final : Base
{
    View(const userver::components::ComponentConfig& cfg,
         const userver::components::ComponentContext& ctx)
        : Base(cfg, ctx),
          token_controller(ctx.FindComponent<controllers::token::Controller>()),
          user_controller(ctx.FindComponent<controllers::user::Controller>())
    {
    }
    static Resp401 PerformInvalidCredentials()
    {
        Resp401 resp;
        resp().body().description() =
            "Account not founded: login or password invalid";
        resp().body().machine_id() = "INVALID_CREDENTIALS";
        return resp;
    }
    Resps Handle(Request&& req) const override
    {
        auto user = user_controller.GetByCredentials(req.body());
        if (!user)
        {
            return PerformInvalidCredentials();
        }
        auto id = token_controller.CreateNew(user->id());
        Resp200 resp;
        resp().body().token() = id;
        resp().body().user() = user.value();
        return resp;
    }

   protected:
    controllers::token::Controller& token_controller;
    controllers::user::Controller& user_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<View>();
}

}  // namespace views::login
