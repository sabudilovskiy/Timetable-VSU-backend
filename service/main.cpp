#include <openapi/http/openapi_descriptor_fwd.hpp>
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
#include "components/controllers/postgres/faculty/fwd.hpp"
#include "components/controllers/postgres/group_stage/fwd.hpp"
#include "components/controllers/postgres/lesson/fwd.hpp"
#include "components/controllers/postgres/teacher/fwd.hpp"
#include "components/controllers/postgres/token/fwd.hpp"
#include "components/controllers/postgres/user/fwd.hpp"
#include "views/admin/create/view.hpp"
#include "views/admin/list/view.hpp"
#include "views/faculty/list/view.hpp"
#include "views/group-stage/list/view.hpp"
#include "views/hello/view.hpp"
#include "views/login/view.hpp"
#include "views/register/view.hpp"
#include "views/teacher/create/view.hpp"
#include "views/teacher/list/view.hpp"
#include "views/teacher/request/approve/link/view.hpp"
#include "views/teacher/request/approve/new/view.hpp"
#include "views/teacher/request/list/view.hpp"
#include "views/test-openapi-view-register/view.hpp"
#include "views/test-openapi-view/view.hpp"
#include "views/timetable/get/view.hpp"

void AppendPgControllers(userver::components::ComponentList& component_list)
{
    using namespace components::controllers::postgres;
    user::Append(component_list);
    token::Append(component_list);
    lesson::Append(component_list);
    admin::Append(component_list);
    teacher::Append(component_list);
    faculty::Append(component_list);
    group_stage::Append(component_list);
}

void AppendViews(userver::components::ComponentList& component_list)
{
    using namespace views;
    login::Append(component_list);
    register_::Append(component_list);
    timetable::get::Append(component_list);
    admin::create::Append(component_list);
    admin::list::Append(component_list);
    teacher::list::Append(component_list);
    teacher::create::Append(component_list);
    teacher::requests::list::Append(component_list);
    teacher::requests::approve::link::Append(component_list);
    teacher::requests::approve::new_::Append(component_list);
    faculty::list::Append(component_list);
    group::stage::list::Append(component_list);
    test::login::Append(component_list);
    test::sign_in::Append(component_list);
}

int main(int argc, char* argv[])
{
    auto component_list =
        userver::components::MinimalServerComponentList()
            .Append<userver::server::handlers::Ping>()
            .Append<userver::components::TestsuiteSupport>()
            .Append<userver::components::HttpClient>()
            .Append<userver::clients::dns::Component>()
            .Append<userver::components::Postgres>("postgres-db-1")
            .Append<userver::server::handlers::TestsControl>();
    openapi::http::AppendOpenApiDescriptor(component_list);
    service_template::AppendHello(component_list);
    AppendPgControllers(component_list);
    AppendViews(component_list);

    return userver::utils::DaemonMain(argc, argv, component_list);
}
