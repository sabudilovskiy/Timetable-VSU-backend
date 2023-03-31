#include "Request.hpp"
#include "../../utils/json_type.hpp"
#include "userver/formats/json.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "userver/logging/log.hpp"
#include "userver/server/http/http_request.hpp"

namespace timetable_vsu_backend::views::register_ {
Request Parse(const userver::server::http::HttpRequest& value,
              userver::formats::parse::To<Request>) {
  auto body = userver::formats::json::FromString(value.RequestBody());
  auto login = body["login"].As<std::string>();
  auto password = body["password"].As<std::string>();
  return Request{std::move(login), std::move(password)};
}
}  // namespace timetable_vsu_backend::views::register_