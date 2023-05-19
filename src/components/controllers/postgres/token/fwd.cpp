#include "fwd.hpp"

#include <userver/components/component_list.hpp>

#include "controller.hpp"

namespace timetable_vsu_backend::components::controllers::postgres
{
void AppendTokenController(userver::components::ComponentList& component_list)
{
    component_list.Append<token::Controller>();
}
}  // namespace timetable_vsu_backend::components::controllers::postgres
