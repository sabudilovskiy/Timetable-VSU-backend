#pragma once
namespace userver::components
{
class ComponentList;
}
namespace timetable_vsu_backend::openapi::http
{
void AppendOpenApiDescriptor(userver::components::ComponentList& list);
}
