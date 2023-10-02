#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/server/http/http_status.hpp>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/http_response_serialize.hpp>
#include <utils/convert/json_parse.hpp>

#include "http/ErrorV1.hpp"
#include "models/admin_account/type.hpp"
#include "models/teacher/type.hpp"
#include "models/user/type.hpp"
#include "models/user_type/serialize.hpp"
#include "models/user_type/type.hpp"

namespace timetable_vsu_backend::views::teacher::list
{
using namespace utils::convert;
struct Response200
{
    ArrayProperty<timetable_vsu_backend::models::Teacher, "teachers"> teachers;
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Json;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kOk;
};

}  // namespace timetable_vsu_backend::views::teacher::list
