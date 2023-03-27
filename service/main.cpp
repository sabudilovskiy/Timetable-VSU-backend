#include <userver/components/minimal_server_component_list.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "../src/views/hello/view.hpp"
#include "userver/storages/postgres/component.hpp"
#include "../src/views/login/view.hpp"
#include "../src/views/register/view.hpp"
#include "../src/components/controllers/token_controller_fwd.hpp"
#include "../src/components/controllers/user_controller_fwd.hpp"

int main(int argc, char* argv[]) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::clients::dns::Component>()
                            .Append<userver::components::Postgres>("postgres-db-1")
                            .Append<userver::server::handlers::TestsControl>();

  using namespace timetable_vsu_backend::components;
  using namespace timetable_vsu_backend::views;
  service_template::AppendHello(component_list);
  timetable_vsu_backend::views::login::Append(component_list);
  timetable_vsu_backend::views::register_::Append(component_list);
  AppendUserController(component_list);
  AppendTokenController(component_list);
  return userver::utils::DaemonMain(argc, argv, component_list);
}
