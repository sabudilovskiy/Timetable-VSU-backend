#include "fwd.hpp"

#include <userver/components/component_list.hpp>

#include "controller.hpp"

namespace timetable_vsu_backend::components::controllers::postgres
{
void AppendUserController(userver::components::ComponentList& component_list)
{
    component_list.Append<user::Controller>();
}
}  // namespace timetable_vsu_backend::components::controllers::postgres
