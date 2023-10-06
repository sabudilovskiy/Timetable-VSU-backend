#include <openapi/http/handler.hpp>
#include <openapi/http/openapi_descriptor.hpp>
#include <openapi/http/openapi_descriptor_fwd.hpp>
#include <userver/components/component_list.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

namespace timetable_vsu_backend::openapi::http
{
void AppendOpenApiDescriptor(userver::components::ComponentList& list)
{
    list.Append<OpenApiDescriptor>();
}
userver::yaml_config::Schema OpenApiDescriptor::GetStaticConfigSchema()
{
    return userver::yaml_config::MergeSchemas<
        userver::server::handlers::HttpHandlerBase>(
        R"(
type: object
description: Class describe by openapi server
additionalProperties: true
properties:
  servers:
    description: servers section in openapi
    type: array
    items:
      description: one server
      type: object
      properties: {}
      additionalProperties: true
  info:
    type: object
    description: info section in openapi
    properties:
      title:
        type: string
        description: info_titile
      description:
        type: string
        description: info_description
      version:
        type: string
        description: info_version
    additionalProperties: true
)");
}
}  // namespace timetable_vsu_backend::openapi::http
