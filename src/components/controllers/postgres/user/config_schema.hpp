#pragma once
#include <string>
namespace timetable_vsu_backend::components::controllers::postgres::config {
const std::string schema =
    R"(
type: object
description: user component smth
additionalProperties: false
properties:
    root_login:
        type: string
        description: login for the superuser 
    root_password:
        type: string
        description: password for the superuser 
)";
}
