#pragma once

#include <openapi/base/doc.hpp>
#include <openapi/base/object_property.hpp>
#include <openapi/doc/serialize/base.hpp>
#include <openapi/doc/serialize/body.hpp>
#include <openapi/doc/serialize/request.hpp>
#include <openapi/doc/serialize/response.hpp>
#include <openapi/http/base/response_property.hpp>
#include <string_view>
#include <type_traits>
namespace timetable_vsu_backend::openapi
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

template <typename Req, typename... Resp>
void AppendPath(Doc& doc, HandlerInfo handler_info, std::type_identity<Req> req,
                std::type_identity<Resp>... resp)
{
    auto& root = doc();
    auto& [path, method] = handler_info;
    std::string path_low;
    for (auto ch : path){
        path_low.append(tolower(ch), 1);
    }
    auto view = root["paths"][path][method];
    auto req_place = view["request"];
    auto responses = view["responses"];
    PlaceRefToRequest<Req>(req_place);
    AppendRequest(doc, req);
    (AppendPathResponse(doc, responses, resp), ...);
}
}  // namespace timetable_vsu_backend::openapi
