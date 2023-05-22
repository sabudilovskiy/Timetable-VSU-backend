#pragma once
#include "http/ErrorV1.hpp"

//Для большинства ошибок данного этого формата будет за глаза
namespace timetable_vsu_backend::utils::common_errors
{
using Response400 =
    http::ErrorV1<userver::server::http::HttpStatus::kBadRequest>;

using Response401 =
    http::ErrorV1<userver::server::http::HttpStatus::kUnauthorized>;

using Response403 =
    http::ErrorV1<userver::server::http::HttpStatus::kForbidden>;

struct Response500
{
    static constexpr convert::TypeOfBody kTypeOfBody =
        convert::TypeOfBody::Empty;
    static constexpr convert::PolicyFields kPolicyFields =
        convert::PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kInternalServerError;
};
}  // namespace timetable_vsu_backend::utils::common_errors
