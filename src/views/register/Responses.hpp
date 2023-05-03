#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>

#include "http/ErrorV1.hpp"
#include "models/user/type.hpp"
#include "models/user_type/serialize.hpp"
#include "models/user_type/type.hpp"
#include "utils/convert/base.hpp"
#include "utils/convert/http_response_serialize.hpp"
#include "utils/convert/json_parse.hpp"

namespace timetable_vsu_backend::views::register_ {
using namespace utils::convert;
struct Response200 {
    Property<boost::uuids::uuid, "token"> id;
    Property<timetable_vsu_backend::models::User, "user"> user;
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Json;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kOk;
};
using Response400 =
    http::ErrorV1<userver::server::http::HttpStatus::kBadRequest>;
struct Response500 {
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Empty;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kInternalServerError;
};
}  // namespace timetable_vsu_backend::views::register_
