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
#include "models/user_type/type.hpp"

namespace timetable_vsu_backend::views::login {

namespace {
using components::controllers::postgres::TokenController;
using components::controllers::postgres::UserController;
class Handler final : public http::HandlerParsed<Request, Response200,
                                                 Response401, Response500> {
    static Response401 PerformInvalidCredentials() {
        Response401 resp;
        resp.description = "Account not founded: login or password invalid";
        resp.machine_id = "INVALID_CREDENTIALS";
        return resp;
    }

   public:
    static constexpr std::string_view kName = "handler-login";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          user_controller(context.FindComponent<UserController>()),
          token_controller(context.FindComponent<TokenController>()) {
    }

    Response Handle(Request&& request) const override {
        auto user = user_controller.GetByLogin(request.login());
        if (!user || user->password != request.password()) {
            return PerformInvalidCredentials();
        }
        auto id = token_controller.CreateNew(
            user->id, userver::utils::datetime::Now() + std::chrono::hours(24));
        if (!id) {
            LOG_WARNING() << fmt::format(
                "Failed to create token for user, id: {}",
                boost::uuids::to_string(user->id.GetUnderlying()));
            return Response500{};
        }
        return Response200{{*id}, {models::UserType::kUser}};
    }

   private:
    const UserController& user_controller;
    const TokenController& token_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list) {
    component_list.Append<Handler>();
}

}  // namespace timetable_vsu_backend::views::login
