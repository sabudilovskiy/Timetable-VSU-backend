#include "view.hpp"

#include <chrono>
#include <exception>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>

#include "Request.hpp"
#include "Responses.hpp"
#include "components/controllers/postgres/token/controller.hpp"
#include "components/controllers/postgres/user/controller.hpp"
#include "http/handler_parsed.hpp"
#include "models/auth_token/serialize.hpp"
#include "models/user/serialize.hpp"
#include "models/user_type/serialize.hpp"

namespace timetable_vsu_backend::views::login {

static_assert(
    userver::formats::common::impl::kHasSerialize<
        userver::formats::json::Value, timetable_vsu_backend::models::User>);
namespace {
namespace pg = components::controllers::postgres;
class Handler final : public http::HandlerParsed<Request, Response200,
                                                 Response401, Response500> {
    static Response401 PerformInvalidCredentials() {
        Response401 resp;
        resp.description = "Account not founded: login or password invalid";
        resp.machine_id = "INVALID_CREDENTIALS";
        return resp;
    }

   public:
    [[maybe_unused]] static constexpr std::string_view kName = "handler-login";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          user_controller(context.FindComponent<pg::user::Controller>()),
          token_controller(context.FindComponent<pg::token::Controller>()) {
    }

    Response Handle(Request&& request) const override {
        auto user = user_controller.GetByCredentials(request);
        if (!user) {
            return PerformInvalidCredentials();
        }
        auto id = token_controller.CreateNew(
            user->id(),
            userver::utils::datetime::Now() + std::chrono::hours(24));
        if (!id) {
            LOG_WARNING() << fmt::format(
                "Failed to create token for user, id: {}",
                boost::uuids::to_string(user->id()));
            return Response500{};
        }
        Response200 resp;
        resp.id() = *id;
        resp.user() = *user;
        return resp;
    }

   private:
    const pg::user::Controller& user_controller;
    const pg::token::Controller& token_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list) {
    component_list.Append<Handler>();
}

}  // namespace timetable_vsu_backend::views::login
