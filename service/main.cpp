#include <userver/components/minimal_server_component_list.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "../src/views/hello/view.hpp"
#include "userver/logging/log.hpp"
#include "userver/storages/postgres/component.hpp"
#include "../src/views/login/view.hpp"
#include "../src/views/register/view.hpp"
#include "../src/components/controllers/token_controller_fwd.hpp"
#include "../src/components/controllers/user_controller_fwd.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;

void LogAllFiles(fs::path path){
  std::stringstream buffer;
  LOG_ERROR() << path;
  for (const auto & entry : fs::directory_iterator(path))
        buffer << entry.path() << ' ';
  LOG_ERROR() << buffer.str();
}

void LogCommands(int argc, char** argv){
  std::stringstream buffer;
  if (argc == 0){
    LOG_ERROR() << "No commands";
  }
  for (int i = 0; i < argc; i++){
    buffer << argv[i] << ' ';
  }
  LOG_ERROR() << fmt::format("Commands is {}", buffer.str());
}

void LogFile(std::string_view path){
  std::string path_str(path);
  std::ifstream file(path_str);
  std::string temp;
  if (!file.is_open()){
    std::stringstream buffer;
    buffer << strerror(errno);
    LOG_ERROR() << fmt::format("{} ifstream fail: {} ", path, buffer.str());
  }
  else if (file.eof()){
    LOG_ERROR() << fmt::format("{} is empty", path);
  }
  while (std::getline(file, temp)){
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
  using namespace timetable_vsu_backend::components;
  using namespace timetable_vsu_backend::views;
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::clients::dns::Component>()
                            .Append<userver::components::Postgres>("postgres-db-1")
                            .Append<userver::server::handlers::TestsControl>();
  service_template::AppendHello(component_list);
  timetable_vsu_backend::views::login::Append(component_list);
  timetable_vsu_backend::views::register_::Append(component_list);
  AppendUserController(component_list);
  AppendTokenController(component_list);
  return userver::utils::DaemonMain(argc, argv, component_list);
}
