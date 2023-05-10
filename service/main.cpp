#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>
#include <utility>

#include "components/controllers/postgres/admin/fwd.hpp"
#include "components/controllers/postgres/lesson/fwd.hpp"
#include "components/controllers/postgres/token/fwd.hpp"
#include "components/controllers/postgres/user/fwd.hpp"
#include "views/get-timetable/view.hpp"
#include "views/hello/view.hpp"
#include "views/login/view.hpp"
#include "views/register/view.hpp"
#include "views/root/create-admin/view.hpp"

int main(int argc, char* argv[]) {
    using namespace timetable_vsu_backend;
    auto component_list =
        userver::components::MinimalServerComponentList()
            .Append<userver::server::handlers::Ping>()
            .Append<userver::components::TestsuiteSupport>()
            .Append<userver::components::HttpClient>()
            .Append<userver::clients::dns::Component>()
            .Append<userver::components::Postgres>("postgres-db-1")
            .Append<userver::server::handlers::TestsControl>();
    service_template::AppendHello(component_list);
    views::login::Append(component_list);
    views::register_::Append(component_list);
    views::get_timetable::Append(component_list);
    views::root::create_admin::Append(component_list);
    components::controllers::postgres::AppendUserController(component_list);
    components::controllers::postgres::AppendTokenController(component_list);
    components::controllers::postgres::AppendLessonDetailsController(
        component_list);
    components::controllers::postgres::AppendAdminController(component_list);
    return userver::utils::DaemonMain(argc, argv, component_list);
}
