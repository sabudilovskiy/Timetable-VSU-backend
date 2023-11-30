#include "fwd.hpp"

#include <userver/components/component_list.hpp>

#include "controller.hpp"

namespace legacy::components::controllers::postgres::teacher
{
void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Controller>();
}
}  // namespace legacy::components::controllers::postgres::teacher
   // ::components::controllers::postgres::teacher
