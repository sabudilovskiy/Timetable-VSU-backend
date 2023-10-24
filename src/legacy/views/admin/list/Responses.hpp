#pragma once
#include <boost/uuid/uuid.hpp>
#include <openapi/json/serialize/enum.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/server/http/http_status.hpp>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/http_response_serialize.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/perform_common_errors.hpp>

#include "http/ErrorV1.hpp"
#include "legacy/models/admin_account/type.hpp"
#include "legacy/models/user/type.hpp"
#include "legacy/models/user_type/type.hpp"

namespace legacy::views::admin::list
{
using namespace utils::convert;
struct Response200
{
    ArrayProperty<::legacy::models::AdminAccount, "admins"> admins;
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Json;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kOk;
};

using Response400 = utils::common_errors::Response400;

using Response401 = utils::common_errors::Response401;

using Response403 = utils::common_errors::Response403;

using Response500 = utils::common_errors::Response500;
}  // namespace legacy::views::admin::list
