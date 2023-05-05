#include "view.hpp"

#include <fmt/core.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <exception>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/boost_uuid4.hpp>
#include <userver/utils/datetime.hpp>
#include <userver/utils/uuid4.hpp>

#include "Request.hpp"
#include "components/controllers/postgres/token/controller.hpp"
#include "components/controllers/postgres/user/controller.hpp"
#include "http/handler_parsed.hpp"
#include "models/auth_token/serialize.hpp"
#include "models/user/serialize.hpp"
#include "views/register/Responses.hpp"

namespace timetable_vsu_backend::views::register_ {

namespace {
namespace pg = components::controllers::postgres;
using Response = models::AuthToken;
class Handler final : public http::HandlerParsed<Request, Response200,
                                                 Response400, Response500> {
   public:
    static constexpr std::string_view kName = "handler-register";
    using http::HandlerParsed<Request, Response200, Response400,
                              Response500>::HandlerParsed;
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          user_controller(context.FindComponent<pg::user::Controller>()),
          token_controller(context.FindComponent<pg::token::Controller>()) {
    }

    Response Handle(Request&& request) const override {
        auto user_id = user_controller.TryToAdd(request);
        if (!user_id) {
            LOG_DEBUG() << fmt::format("Cannot create user, login: {}",
                                       request.login());
            return Response400{};
        }
        auto id = token_controller.CreateNew(
            *user_id, userver::utils::datetime::Now() + std::chrono::hours(24));
        if (!id) {
            LOG_WARNING() << fmt::format(
                "Failed to create token for user, id: {}", *user_id);
            return Response500{};
        }
        Response200 resp;
        resp.id() = *id;
        resp.user() =
            models::User{.id = {*user_id}, .type = {models::UserType::kUser}};
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

}  // namespace timetable_vsu_backend::views::register_
