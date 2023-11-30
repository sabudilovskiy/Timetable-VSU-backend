#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <utility>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/http_request_parse.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/parse/uuid/string.hpp>

#include "legacy/models/auth_token/type.hpp"
#include "legacy/models/teacher_info/type.hpp"
namespace legacy::views::teacher::create
{
using namespace utils::convert;
struct Request
{
    Property<legacy::models::TeacherInfo, "teacher_info"> teacher_info;
    HeaderProperty<boost::uuids::uuid, "token"> token;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
};
}  // namespace legacy::views::teacher::create
