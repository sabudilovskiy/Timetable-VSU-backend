#include "fwd.hpp"

#include <userver/components/component_list.hpp>

#include "controller.hpp"

namespace components::controllers::postgres::group_stage
{
void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Controller>();
}
}  // namespace components::controllers::postgres::group_stage
   // ::components::controllers::postgres::group_stage
