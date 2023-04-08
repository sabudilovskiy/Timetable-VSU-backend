#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>

#include "utils/convert/base.hpp"
#include "utils/convert/http_response_serialize.hpp"
#include "utils/convert/json_parse.hpp"

namespace timetable_vsu_backend::views::login {
using namespace utils::convert;
struct Response200 {
    Property<boost::uuids::uuid, "token"> id;
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Json;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kOk;
};
struct Response401 {
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Empty;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kUnauthorized;
};
struct Response500 {
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Empty;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kInternalServerError;
};
}  // namespace timetable_vsu_backend::views::login