#pragma once

#include <fmt/core.h>

#include <exception>
#include <openapi/base/doc.hpp>
#include <openapi/base/properties/object.hpp>
#include <openapi/base/reflective/checks.hpp>
#include <openapi/doc/path.hpp>
#include <openapi/http/base/request_info.hpp>
#include <openapi/http/base/response_info.hpp>
#include <openapi/http/openapi_descriptor.hpp>
#include <string_view>
#include <type_traits>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/formats/json/inline.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/http/content_type.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/yaml_config/schema.hpp>
#include <utils/constexpr_string.hpp>
#include <variant>

namespace openapi::http
{
template <utils::ConstexprString Name, checks::IsReflective Req,
          typename... Responses>
struct OpenApiHandler : public userver::server::handlers::HttpHandlerBase
{
    [[maybe_unused]] static constexpr auto kName = Name;
    using Resps = std::variant<Responses...>;
    OpenApiHandler(const userver::components::ComponentConfig& cfg,
                   const userver::components::ComponentContext& ctx)
        : userver::server::handlers::HttpHandlerBase(cfg, ctx)
    {
        auto descriptor = ctx.FindComponentOptional<OpenApiDescriptor>();
        if (descriptor)
        {
            AppendSchema(descriptor->GetDoc());
        }
    }

    static std::string DoHandleAfterParse(
        const userver::server::http::HttpRequest& http_req,
        ResponseInfo& resp_info)
    {
        WriteResponseInfo(http_req, resp_info);
        return std::move(resp_info.body);
    }
    std::string DoHandleAfterParse(
        const userver::server::http::HttpRequest& http_req, Req& req) const
    {
        auto resp = Handle(std::move(req));
        auto resp_info = SerializeResponse(resp);
        return DoHandleAfterParse(http_req, resp_info);
    }

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& http_req,
        userver::server::request::RequestContext&) const override
    {
        auto info = MakeInfoFromRequest(http_req);
        std::variant<Req, ResponseInfo> req = ParseRequest(info);
        return std::visit(
            [this, &http_req](auto& req) {
                return this->DoHandleAfterParse(http_req, req);
            },
            req);
    }

    virtual Resps Handle(Req&&) const = 0;

   protected:
    static std::variant<Req, ResponseInfo> ParseRequest(
        RequestInfo request_info)
    {
        try
        {
            return Parse(request_info, userver::formats::parse::To<Req>{});
        }
        catch (std::exception& exc)
        {
            std::string body_error = fmt::format(R"(
                "message" : "Some error happens where server tried to parse request: {}"
            )",
                                                 exc.what());
            return Perform400(std::move(body_error));
        }
    }

    static ResponseInfo Perform400(std::string msg)
    {
        return ResponseInfo{
            .userver_code = userver::server::http::HttpStatus::kBadRequest,
            .body = std::move(msg)};
    }

    static ResponseInfo Perform500(std::string msg)
    {
        return ResponseInfo{
            .userver_code = userver::server::http::HttpStatus::kBadRequest,
            .body = std::move(msg)};
    }

    static void WriteResponseInfo(const userver::server::http::HttpRequest& req,
                                  const ResponseInfo& info)
    {
        req.SetResponseStatus(info.userver_code);
        for (auto& [key, value] : info.headers)
        {
            req.GetHttpResponse().SetHeader(key, value);
        }
        switch (info.response_body_type)
        {
            case ResponseBodyType::kText:
                req.GetHttpResponse().SetContentType(
                    userver::http::content_type::kTextPlain);
                break;
            case ResponseBodyType::kJson:
                req.GetHttpResponse().SetContentType(
                    userver::http::content_type::kApplicationJson);
                break;
        }
    }

    static ResponseInfo SerializeResponse(const Resps& response)
    {
        try
        {
            auto visiter = [](auto& resp) -> ResponseInfo {
                return Serialize(
                    resp, userver::formats::serialize::To<ResponseInfo>{});
            };
            return std::visit(visiter, response);
        }
        catch (std::exception& exc)
        {
            std::string_view msg_body = R"(
                    Some unexpected error happens when the server tried to serialize response. Sorry.
            )";
            LOG_ERROR() << "Unexpected error from serialize: " << exc.what();
            return Perform500(ToString(
                userver::formats::json::MakeObject("message", msg_body)));
        }
    }
    void AppendSchema(Doc& doc) const
    {
        const userver::server::handlers::HandlerConfig& config = GetConfig();
        if (config.path.index() == 1)
        {
            return;
        }
        HandlerInfo info{.path = std::get<0>(config.path),
                         .method = config.method};
        AppendPath(doc, info, std::type_identity<Req>{},
                   std::type_identity<Responses>{}...);
    }
};
}  // namespace openapi::http
