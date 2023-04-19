#pragma once
#include <fmt/core.h>
#include <fmt/format.h>

#include <exception>
#include <optional>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_status.hpp>
#include <utility>

#include "../utils/convert/http_response_base.hpp"

namespace timetable_vsu_backend::http {
template <typename Request, typename... TResponse>
class HandlerParsed : public userver::server::handlers::HttpHandlerBase {
   public:
    using Response = std::variant<TResponse...>;
    using HttpHandlerBase::HttpHandlerBase;
    HandlerParsed(const userver::components::ComponentConfig& config,
                  const userver::components::ComponentContext& context)
        : HttpHandlerBase(config, context) {
    }
    virtual Response Handle(Request&& request) const = 0;

   private:
    static std::optional<Request> ParseUserRequest(
        const userver::server::http::HttpRequest& raw_request) {
        std::optional<Request> request;
        try {
            static_assert(userver::formats::common::impl::kHasParse<
                              userver::server::http::HttpRequest, Request>,
                          "Request should be able to parse from "
                          "userver::server::http::HttpRequest");
            LOG_DEBUG() << "Start parse request";
            request =
                Parse(raw_request, userver::formats::parse::To<Request>{});
            LOG_DEBUG() << "End parse request";
            return request;
        } catch (std::exception& exc) {
            LOG_DEBUG() << fmt::format(
                "Can't parse user request, return 400. Error: {}", exc.what());
            request = std::nullopt;
        }
        return request;
    }

    using HttpStatus = userver::server::http::HttpStatus;

    template <typename SomeResponse>
    static std::string SerializeResponse(
        SomeResponse& some_response,
        const userver::server::http::HttpRequest& raw_request) {
        std::string body;
        timetable_vsu_backend::utils::convert::HttpResponse convert_response{
            raw_request.GetHttpResponse(), body};
        Serialize(some_response, convert_response);
        return body;
    }
    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& raw_request,
        userver::server::request::RequestContext& /*context*/)
        const override final {
        auto& http_response = raw_request.GetHttpResponse();
        auto request = ParseUserRequest(raw_request);
        if (!request) {
            LOG_DEBUG() << "Fail parse";
            http_response.SetStatus(HttpStatus::kBadRequest);
            return {};
        }
        try {
            LOG_DEBUG() << "Start handle parsed request";
            Request&& parsed_request = std::move(*request);
            auto response = Handle(std::move(parsed_request));
            LOG_DEBUG() << "End handle parsed request";
            auto visiter = [&raw_request](auto& value) {
                return SerializeResponse(value, raw_request);
            };
            return std::visit(visiter, response);
        } catch (std::exception& exc) {
            http_response.SetStatus(HttpStatus::kInternalServerError);
            LOG_ERROR() << fmt::format(
                "Unexpected error while handle request: {}", exc.what());
            return {};
        }
    }
};
}  // namespace timetable_vsu_backend::http