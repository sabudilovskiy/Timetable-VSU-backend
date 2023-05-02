#include "fwd.hpp"

#include <userver/components/component_list.hpp>

#include "controller.hpp"

namespace timetable_vsu_backend::components::controllers::postgres {
void AppendLessonDetailsController(
    userver::components::ComponentList& component_list) {
    component_list.Append<LessonDetailsController>();
}
}  // namespace timetable_vsu_backend::components::controllers::postgres
