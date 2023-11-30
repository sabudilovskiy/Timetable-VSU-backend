#pragma once
namespace userver::components
{
class ComponentList;
}
namespace openapi::http
{
void AppendOpenApiDescriptor(userver::components::ComponentList& list);
}
