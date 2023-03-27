#include "Request.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "userver/logging/log.hpp"
#include "userver/server/http/http_request.hpp"
#include "userver/formats/json.hpp"
#include "../../utils/json_type.hpp"


namespace timetable_vsu_backend::views::register_{
    Request Parse(const userver::server::http::HttpRequest& value, userver::formats::parse::To<Request>){
        auto body = userver::formats::json::FromString(value.RequestBody());
        LOG_CRITICAL() << fmt::format("try parse: {}", userver::formats::json::ToString(body));
        LOG_CRITICAL() << fmt::format("login type : {}", utils::GetType(body["login"]));
        auto login = body["login"].As<std::string>();
        LOG_CRITICAL() << fmt::format("register type : {}", utils::GetType(body["password"]));
        auto password = body["password"].As<std::string>();
        return Request {
            std::move(login), 
            std::move(password)
        };
    }
}