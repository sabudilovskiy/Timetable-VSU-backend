#include "token_controller_fwd.hpp"
#include "token_controller.hpp"
#include "userver/components/component_list.hpp"

namespace timetable_vsu_backend::components {
void AppendTokenController(userver::components::ComponentList& component_list) {
  component_list.Append<TokenController>();
}
}  // namespace timetable_vsu_backend::components