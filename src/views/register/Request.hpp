#pragma once
#include <string>
#include <userver/formats/parse/to.hpp>

namespace userver::server::http {
class HttpRequest;
}

namespace timetable_vsu_backend::views::register_ {
struct Request {
    std::string login;
    std::string password;
};
Request Parse(const userver::server::http::HttpRequest& value,
              userver::formats::parse::To<Request>);
}  // namespace timetable_vsu_backend::views::register_