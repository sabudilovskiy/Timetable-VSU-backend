#pragma once
#include <utils/component_list_fwd.hpp>

namespace timetable_vsu_backend::components::controllers::postgres
{
namespace teacher
{
class Controller;
void Append(userver::components::ComponentList& component_list);
}  // namespace teacher

}  // namespace timetable_vsu_backend::components::controllers::postgres
