#pragma once

#include <openapi/base/doc.hpp>
#include <openapi/base/properties/object.hpp>
#include <openapi/doc/base.hpp>
#include <openapi/doc/body.hpp>
#include <openapi/doc/request.hpp>
#include <openapi/doc/response.hpp>
#include <openapi/http/base/response_property.hpp>
#include <string_view>
#include <type_traits>
#include <userver/logging/log.hpp>
namespace openapi
{
struct HandlerInfo
{
    const std::string& path;
    const std::string& method;
};

template <typename Resp, typename Traits>
void AppendPathResponse(
    Doc& doc, userver::formats::yaml::ValueBuilder& view,
    std::type_identity<http::ResponseProperty<Resp, Traits>>)
{
    auto status_code = static_cast<int>(Traits::code);
    std::string code_str = std::to_string(status_code);
    auto resp = view[code_str];
    AppendResponse(doc, std::type_identity<Resp>{});
    PlaceRefToResponse<Resp>(resp);
}

namespace impl
{
inline std::vector<std::string> split_methods(HandlerInfo handler_info)
{
    std::string method_low;
    std::vector<std::string> methods;
    for (auto ch : handler_info.method)
    {
        if (ch != ',')
        {
            method_low.append(1, tolower(ch));
        }
        else
        {
            methods.emplace_back(std::move(method_low));
        }
    }
    if (!method_low.empty())
    {
        methods.emplace_back(std::move(method_low));
    }
    return methods;
}
}  // namespace impl

template <typename Req, typename... Resp>
void AppendPath(Doc& doc, HandlerInfo handler_info, std::type_identity<Req> req,
                std::type_identity<Resp>... resp)
{
    auto& root = doc();
    auto& [path, method_raw] = handler_info;
    auto methods = impl::split_methods(handler_info);
    for (auto& method : methods)
    {
        auto view = root["paths"][path][method];
        AppendRequest(DocHelper{doc(), view}, req);
        auto responses = view["responses"];
        (AppendPathResponse(doc, responses, resp), ...);
    }
}
}  // namespace openapi
