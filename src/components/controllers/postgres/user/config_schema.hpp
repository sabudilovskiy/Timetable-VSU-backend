#pragma once
#include <string>
namespace timetable_vsu_backend::components::controllers::postgres::user::config {
const std::string schema =
    R"(
type: object
description: Компонент, отвечающий за авторизацию и определение типа пользователей
additionalProperties: false
properties:
    root:
        type: object
        description: Настройки суперпользователя. Он будет создан на время работы сервиса, а затем будет удален из БД. Если логин занят, то суперпользователь не будет создан.
        additionalProperties: false
        properties:
            login:
                type: string
                description: Логин для суперпользователя
            password:
                type: string
                description: Пароль для суперпользователя 
)";
}
