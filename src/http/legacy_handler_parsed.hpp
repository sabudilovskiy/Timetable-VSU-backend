#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <exception>
#include <optional>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include "userver/formats/json/value.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "userver/server/http/http_status.hpp"

namespace timetable_vsu_backend::http {
template <typename Request, typename Response>
class LegacyHandlerParsed : public userver::server::handlers::HttpHandlerBase {
 public:
  using HttpHandlerBase::HttpHandlerBase;
  using HttpStatus = userver::server::http::HttpStatus;
  LegacyHandlerParsed(const userver::components::ComponentConfig& config,
                      const userver::components::ComponentContext& context)
      : HttpHandlerBase(config, context) {}
  virtual Response Handle(
      Request&& request,
      userver::server::http::HttpResponse& response) const = 0;
  static std::optional<Request> ParseUserRequest(
      const userver::server::http::HttpRequest& raw_request) {
    std::optional<Request> request;
    try {
      request = Parse(raw_request, userver::formats::parse::To<Request>{});
      return request;
    } catch (std::exception& exc) {
      LOG_DEBUG() << fmt::format(
          "Can't parse user request, return 400. Error: {}", exc.what());
      return std::nullopt;
    }
  }
  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& raw_request,
      userver::server::request::RequestContext& /*context*/) const override {
    auto& http_response = raw_request.GetHttpResponse();
    auto request = ParseUserRequest(raw_request);
    if (!request) {
      http_response.SetStatus(HttpStatus::kBadRequest);
      return {};
    }
    try {
      auto response = Handle(std::move(*request), http_response);
      userver::formats::json::Value json = Serialize(
          response,
          userver::formats::serialize::To<userver::formats::json::Value>{});
      return userver::formats::json::ToString(json);
    } catch (std::exception& exc) {
      http_response.SetStatus(HttpStatus::kInternalServerError);
      LOG_ERROR() << fmt::format("Unexpected error while handle request: {}",
                                 exc.what());
      return {};
    }
  }
};
}  // namespace timetable_vsu_backend::http