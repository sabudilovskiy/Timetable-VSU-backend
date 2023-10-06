#pragma once

#include <openapi/base/doc.hpp>
#include <userver/components/component_config.hpp>
#include <userver/formats/yaml/serialize.hpp>
#include <userver/http/content_type.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

namespace timetable_vsu_backend::openapi::http
{
struct OpenApiDescriptor : public userver::server::handlers::HttpHandlerBase
{
    static constexpr std::string_view kName = "openapi-descriptor";
    OpenApiDescriptor(const userver::components::ComponentConfig& cfg,
                      const userver::components::ComponentContext& ctx)
        : userver::server::handlers::HttpHandlerBase(cfg, ctx)
    {
        doc()["info"] = cfg["info"].Yaml();
        doc()["openapi"] = "3.0.0";
        doc()["servers"] = cfg["servers"].Yaml();
    }
    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& req,
        userver::server::request::RequestContext&) const override
    {
        req.SetResponseStatus(userver::server::http::HttpStatus::kOk);
        req.GetHttpResponse().SetContentType(
            userver::http::content_type::kTextPlain);
        return schema;
    }

    void OnAllComponentsLoaded() override
    {
        schema = ToString(doc().ExtractValue());
    }
    Doc& GetDoc()
    {
        return doc;
    }

    static userver::yaml_config::Schema GetStaticConfigSchema();

   private:
    Doc doc;
    std::string schema;
};
}  // namespace timetable_vsu_backend::openapi::http
