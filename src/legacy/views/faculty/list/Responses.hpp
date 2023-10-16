#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/server/http/http_status.hpp>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/http_response_serialize.hpp>
#include <utils/convert/json_parse.hpp>

#include "http/ErrorV1.hpp"
#include "legacy/models/admin_account/type.hpp"
#include "legacy/models/faculty/type.hpp"
#include "legacy/models/user/type.hpp"
#include "legacy/models/user_type/serialize.hpp"
#include "legacy/models/user_type/type.hpp"

namespace legacy::views::faculty::list
{
using namespace utils::convert;
struct Response200
{
    ArrayProperty<legacy::models::Faculty, "faculties"> faculties;
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Json;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kOk;
};

}  // namespace legacy::views::faculty::list
