cmake_minimum_required(VERSION 3.12)
project(timetable_vsu_backend CXX)

include(third_party/userver/cmake/SetupEnvironment.cmake)
include(GNUInstallDirs)

add_subdirectory(third_party/userver)


# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
    src/views/hello/view.hpp
    src/views/hello/view.cpp
	src/components/controllers/user_controller.cpp
	src/components/controllers/user_controller.hpp
	src/components/controllers/user_controller_fwd.hpp
	src/components/controllers/user_controller_fwd.cpp
	src/components/controllers/token_controller_fwd.cpp
	src/components/controllers/user_controller_fwd.cpp
	src/components/controllers/token_controller.hpp
	src/components/controllers/token_controller.cpp
	src/models/auth_token/type.hpp
	src/models/auth_token/serialize.hpp
	src/http/handler_parsed.hpp
	src/models/user/type.hpp
	src/models/user_type/parse.cpp
	src/models/user_type/parse.hpp
	src/models/user_type/postgre.hpp
	src/models/user_type/type.hpp
	src/utils/component_list_fwd.hpp
	src/utils/json_type.cpp
	src/utils/json_type.hpp
	src/views/login/Request.cpp
	src/views/login/Request.hpp
	src/views/login/view.cpp
	src/views/login/view.hpp
	src/views/register/Request.cpp
	src/views/register/Request.hpp
	src/views/register/view.cpp
	src/views/register/view.hpp
)
target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver-core userver-postgresql)


# The Service
add_executable(${PROJECT_NAME} service/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
add_executable(${PROJECT_NAME}_unittest
    utests/hello_test.cpp
)
target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs userver-utest)
add_google_tests(${PROJECT_NAME}_unittest)


# Benchmarks
add_executable(${PROJECT_NAME}_benchmark
	benchs/hello_benchmark.cpp
)
target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME}_objs userver-ubench)
add_google_benchmark_tests(${PROJECT_NAME}_benchmark)

# Functional Tests
add_subdirectory(tests)

if(DEFINED ENV{PREFIX})
	message(STATUS "Set install prefix: $ENV{PREFIX}")
	file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
	set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
endif()

set(CONFIG_VAR_PATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME}/config_vars.yaml)
set(CONFIG_FALLBACK_PATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME}/dynamic_config_fallback.json)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configs/static_config.yaml.in ${CMAKE_CURRENT_SOURCE_DIR}/configs/static_config.yaml)

FILE(GLOB CONFIGS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.yaml ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})
