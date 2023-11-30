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
#include "legacy/models/user_type/type.hpp"
#include "models/error_v1/type.hpp"

namespace views::Register
{
namespace
{
using Resp200 = Resp<Response, 200>;
using Resp400 = Resp<models::ResponseErrorV1, 400>;
using Base =
    openapi::http::OpenApiHandler<"register-view", Request, Resp200, Resp400>;
struct View final : Base
{
    View(const userver::components::ComponentConfig& cfg,
         const userver::components::ComponentContext& ctx)
        : Base(cfg, ctx),
          token_controller(ctx.FindComponent<controllers::token::Controller>()),
          user_controller(ctx.FindComponent<controllers::user::Controller>())
    {
    }
    static Resp400 PerformLoginTaken()
    {
        Resp400 resp400;
        resp400().body().machine_id() = "LOGIN_ALREADY_TAKEN";
        resp400().body().description() =
            "This login is busy, please use another one.";
        return resp400;
    }
    Resps Handle(Request&& req) const override
    {
        auto transaction = user_controller.CreateTransaction(
            utils::SafeTranscaction::ActionOnDeath::kRollback);
        auto user_id = user_controller.TryToAdd(req.body().user_credentials(),
                                                transaction);
        if (!user_id)
        {
            return PerformLoginTaken();
        }
        auto id = token_controller.CreateNew(*user_id, transaction);
        // clang-format off
        user_controller.CreateRequestRights(
            *user_id, 
            req.body().description().value_or(""),
            req.body().desired_type().value_or(legacy::models::UserType::user),
            transaction
        );
        transaction->Commit();
        Resp200 resp;
        resp().body().token() = id;
        resp().body().user() = models::User{
            .id = {*user_id},
            .type = {legacy::models::UserType::user}
        };
        // clang-format on
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

}  // namespace views::Register
