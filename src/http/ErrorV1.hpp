#pragma once
#include <userver/server/http/http_status.hpp>

#include "../utils/convert/base.hpp"

namespace timetable_vsu_backend::http {
namespace convert = timetable_vsu_backend::utils::convert;
template <userver::server::http::HttpStatus code>
struct ErrorV1 {
    static constexpr convert::TypeOfBody kTypeOfBody =
        convert::TypeOfBody::Json;
    static constexpr convert::PolicyFields kPolicyFields =
        convert::PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode = code;
    convert::Property<std::string, "description"> description;
    convert::Property<std::string, "machine_id"> machine_id;
};
}  // namespace timetable_vsu_backend::http