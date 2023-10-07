#pragma once
#include <utils/component_list_fwd.hpp>

namespace components::controllers::postgres
{
namespace teacher
{
class Controller;
void Append(userver::components::ComponentList& component_list);
}  // namespace teacher

}  // namespace components::controllers::postgres
