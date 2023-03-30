#include "Request.hpp"
#include <fmt/core.h>
#include "userver/formats/json/value_builder.hpp"
#include "userver/formats/yaml/serialize.hpp"
#include "userver/logging/log.hpp"
#include "userver/server/http/http_request.hpp"
#include "userver/formats/json.hpp"

struct Test{
    std::string id;
};


namespace timetable_vsu_backend::views::login{
    Request Parse(const userver::server::http::HttpRequest& value, userver::formats::parse::To<Request>){
        auto body = userver::formats::json::FromString(value.RequestBody());
        Test test{
            .id = "sdsd"
        };
        LOG_DEBUG() << test.id;
        return Request {
            body["login"].As<std::string>(), 
            body["password"].As<std::string>()
        };
    }
}