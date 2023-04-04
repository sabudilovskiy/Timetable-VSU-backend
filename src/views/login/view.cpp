#include "view.hpp"
#include <chrono>
#include <exception>
#include <userver/components/component_list.hpp>
#include "../../components/controllers/token_controller.hpp"
#include "../../components/controllers/user_controller.hpp"
#include "../../http/handler_parsed.hpp"
#include "../../models/auth_token/serialize.hpp"
#include "Request.hpp"
#include "userver/formats/parse/to.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utils/datetime.hpp"

namespace timetable_vsu_backend::views::login {

namespace {
using Response = models::AuthToken;
class LoginHandler final : public http::HandlerParsed<Request, Response> {
 public:
  static constexpr std::string_view kName = "handler-login";
  using http::HandlerParsed<Request, Response>::HandlerParsed;
  LoginHandler(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context)
      : HandlerParsed(config, context),
        user_controller(context.FindComponent<components::UserController>()),
        token_controller(context.FindComponent<components::TokenController>()) {
  }

  Response Handle(
      Request&& request,
      userver::server::http::HttpResponse& http_response) const override {
    auto user = user_controller.GetByLogin(request.login());
    if (!user || user->password != request.password()) {
      http_response.SetStatus(HttpStatus::kUnauthorized);
      return {};
    }
    auto id = token_controller.CreateNew(
        user->id, userver::utils::datetime::Now() + std::chrono::hours(24));
    if (!id) {
      LOG_WARNING() << fmt::format(
          "Failed to create token for user, id: {}",
          boost::uuids::to_string(user->id.GetUnderlying()));
      http_response.SetStatus(HttpStatus::kInternalServerError);
      return {};
    }
    return {*id};
  }

 private:
  const components::UserController& user_controller;
  const components::TokenController& token_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list) {
  component_list.Append<LoginHandler>();
}

}  // namespace timetable_vsu_backend::views::login
