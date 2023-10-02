#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <utility>
#include <utils/convert/base.hpp>
#include <utils/convert/drop_properties_ref.hpp>
#include <utils/convert/http_request_parse.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/parse/uuid/string.hpp>

#include "models/user_credentials/type.hpp"
namespace timetable_vsu_backend::views::admin::create
{
using namespace utils::convert;
struct Request
{
    Property<models::UserCredentials, "credentials"> credentials;
    HeaderProperty<boost::uuids::uuid, "token"> token;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
};
}  // namespace timetable_vsu_backend::views::admin::create
