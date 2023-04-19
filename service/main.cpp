#include <filesystem>
#include <fstream>
#include <sstream>
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

#include "components/controllers/postgres/lesson/fwd.hpp"
#include "components/controllers/postgres/token/fwd.hpp"
#include "components/controllers/postgres/user/fwd.hpp"
#include "views/get-timetable/view.hpp"
#include "views/hello/view.hpp"
#include "views/login/view.hpp"
#include "views/register/view.hpp"

namespace fs = std::filesystem;

void LogAllFiles(fs::path path) {
    std::stringstream buffer;
    LOG_ERROR() << path;
    for (const auto& entry : fs::directory_iterator(path))
        buffer << entry.path() << ' ';
    LOG_ERROR() << buffer.str();
}

void LogCommands(int argc, char** argv) {
    std::stringstream buffer;
    if (argc == 0) {
        LOG_ERROR() << "No commands";
    }
    for (int i = 0; i < argc; i++) {
        buffer << argv[i] << ' ';
    }
    LOG_ERROR() << fmt::format("Commands is {}", buffer.str());
}

void LogFile(std::string_view path) {
    std::string path_str(path);
    std::ifstream file(path_str);
    std::string temp;
    if (!file.is_open()) {
        std::stringstream buffer;
        buffer << strerror(errno);
        LOG_ERROR() << fmt::format("{} ifstream fail: {} ", path, buffer.str());
    } else if (file.eof()) {
        LOG_ERROR() << fmt::format("{} is empty", path);
    }
    while (std::getline(file, temp)) {
        LOG_ERROR() << temp;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    // LogAllFiles(fs::current_path());
    // LogAllFiles("/home/user/.local/etc/timetable_vsu_backend/");
    // LogCommands(argc, argv);
    // //кто это?
    // LogFile("/usr/local/etc/timetable_vsu_backend/config_dev.yaml");
    // LogFile("/home/user/.local/etc/timetable_vsu_backend/config_vars_docker.yaml");
    // LogFile("config_vars.docker.yaml");
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
    components::controllers::postgres::AppendUserController(component_list);
    components::controllers::postgres::AppendTokenController(component_list);
    components::controllers::postgres::AppendLessonDetailsController(
        component_list);
    return userver::utils::DaemonMain(argc, argv, component_list);
}
