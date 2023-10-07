#pragma once
#include <string>
namespace components::controllers::postgres::user::config
{
const std::string schema =
    R"(
type: object
description: Компонент, отвечающий за авторизацию и определение типа пользователей
additionalProperties: false
properties:
    root:
        type: object
        description: Настройки суперпользователя. Он будет создан на время работы сервиса, а затем будет удален из БД. Логин и id будут освобождены для него.
        additionalProperties: false
        properties:
            login:
                type: string
                description: Логин для суперпользователя
            password:
                type: string
                description: Пароль для суперпользователя
            id: 
                type: string
                description: UUID суперпользователя 
)";
}
