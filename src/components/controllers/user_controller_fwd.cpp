#include "token_controller_fwd.hpp"
#include "user_controller.hpp"
#include "userver/components/component_list.hpp"

namespace timetable_vsu_backend::components {
void AppendUserController(userver::components::ComponentList& component_list) {
    component_list.Append<UserController>();
}
}  // namespace timetable_vsu_backend::components