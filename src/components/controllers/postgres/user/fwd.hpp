#pragma once
#include "utils/component_list_fwd.hpp"
namespace timetable_vsu_backend::components::controllers::postgres {
class UserController;
void AppendUserController(userver::components::ComponentList& component_list);
}  // namespace timetable_vsu_backend::components::controllers::postgres