#include "view.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <exception>
#include <userver/components/component_list.hpp>
#include "../../components/controllers/user_controller.hpp"
#include "../../components/controllers/token_controller.hpp"
#include "Request.hpp"
#include "userver/formats/parse/to.hpp"
#include "../../http/handler_parsed.hpp"
#include "userver/logging/log.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utils/boost_uuid4.hpp"
#include "userver/utils/datetime.hpp"
#include <chrono>
#include "../../models/auth_token/serialize.hpp"
#include "userver/utils/uuid4.hpp"


namespace timetable_vsu_backend::views::register_ {

namespace {
using Response = models::AuthToken;
class RegisterHandler final : public http::HandlerParsed<Request, Response> {
 public:
  static constexpr std::string_view kName = "handler-register";
  using http::HandlerParsed<Request, Response>::HandlerParsed;
  RegisterHandler(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context)
      : HandlerParsed(config, context),
        user_controller(context.FindComponent<components::UserController>()),
        token_controller(context.FindComponent<components::TokenController>()) {}

  Response Handle(Request &&request, userver::server::http::HttpResponse &http_response) const override{
    auto uuid = userver::utils::generators::GenerateBoostUuid();
    models::User user{models::User::Id{std::move(uuid)}, request.login, request.password, models::UserType::kUser};
    auto created = user_controller.TryToAdd(user);
    if (!created){
      http_response.SetStatus(HttpStatus::kBadRequest);
      return {};
    }
    auto id = token_controller.CreateNew(user.id, userver::utils::datetime::Now() + std::chrono::hours(24));
    return {id};
  }  

 private:
  const components::UserController& user_controller;
  const components::TokenController& token_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list) {
  component_list.Append<RegisterHandler>();
}

}  // namespace timetable_vsu_backend::views::register
