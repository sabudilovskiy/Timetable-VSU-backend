#pragma once
#include <utils/component_list_fwd.hpp>
namespace components::controllers::postgres
{
namespace user
{
class Controller;
void Append(userver::components::ComponentList& component_list);
}  // namespace user

}  // namespace components::controllers::postgres
