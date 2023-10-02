#include <openapi/http/openapi_descriptor_fwd.hpp>
#include <openapi/http/handler.hpp>
#include "userver/components/component_list.hpp"

namespace timetable_vsu_backend::openapi::http
{
    void AppendOpenApiDescriptor(userver::components::ComponentList& list){
        list.Append<OpenApiDescriptor>();
    }
}