#include "view.hpp"

#include <fmt/core.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <exception>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/boost_uuid4.hpp>
#include <userver/utils/datetime.hpp>
#include <userver/utils/uuid4.hpp>
#include <utils/shared_transaction.hpp>

#include "Request.hpp"
#include "legacy/components/controllers/postgres/token/controller.hpp"
#include "legacy/components/controllers/postgres/user/controller.hpp"
#include "http/handler_parsed.hpp"
#include "legacy/models/auth_token/serialize.hpp"
#include "legacy/models/user/serialize.hpp"
#include "legacy/models/user_type/parse.hpp"
#include "legacy/models/user_type/type.hpp"
#include "legacy/views/register/Responses.hpp"

namespace legacy::views::register_
{
namespace
{
namespace pg = legacy::components::controllers::postgres;
using Response = legacy::models::AuthToken;
class Handler final
    : public http::HandlerParsed<Request, Response200, Response400, Response500>
{
   public:
    static constexpr std::string_view kName = "handler-register";
    using http::HandlerParsed<Request, Response200, Response400,
                              Response500>::HandlerParsed;
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          user_controller(context.FindComponent<pg::user::Controller>()),
          token_controller(context.FindComponent<pg::token::Controller>())
    {
    }
    static Response400 PerformLoginTaken()
    {
        Response400 resp400;
        resp400.machine_id() = "LOGIN_ALREADY_TAKEN";
        resp400.description() = "This login is busy, please use another one.";
        return resp400;
    }
    static Response500 PerformFailToken(const boost::uuids::uuid& user_id)
    {
        LOG_WARNING() << fmt::format("Failed to create token for user, id: {}",
                                     user_id);
        return Response500{};
    }
    void HandleDesiredType(const utils::SharedTransaction& transaction,
                           const Request& request,
                           const boost::uuids::uuid& user_id) const
    {
        using enum legacy::models::UserType;
        switch (request.desired_type().value_or(kUser))
        {
            case kAdmin:
                user_controller.CreateRequestAdmin(
                    user_id, request.description().value_or(""), transaction);
                return;
            case kTeacher:
                user_controller.CreateRequestTeacher(
                    user_id, request.description().value_or(""), transaction);
                return;
            default:
                return;
        }
    }
    Response Handle(Request&& request) const override
    {
        auto transaction = user_controller.CreateTransaction();
        auto user_id =
            user_controller.TryToAdd(request.user_credentials(), transaction);
        if (!user_id)
        {
            return PerformLoginTaken();
        }
        auto id = token_controller.CreateNew(
            *user_id, userver::utils::datetime::Now() + std::chrono::hours(24),
            transaction);
        if (!id)
        {
            return PerformFailToken(user_id.value());
        }
        HandleDesiredType(transaction, request, user_id.value());
        Response200 resp;
        resp.id() = *id;
        resp.user() =
            legacy::models::User{.id = {*user_id}, .type = {legacy::models::UserType::kUser}};
        return resp;
    }

   private:
    const pg::user::Controller& user_controller;
    const pg::token::Controller& token_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Handler>();
}

}  // namespace legacy::views::register_
