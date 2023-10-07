#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <utility>
#include <utils/convert/base.hpp>
#include <utils/convert/http_request_parse.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/parse/uuid/string.hpp>

#include "models/teacher_info/type.hpp"
namespace views::teacher::requests::approve::new_
{
using namespace utils::convert;
struct Request
{
    HeaderProperty<boost::uuids::uuid, "token"> token;
    Property<boost::uuids::uuid, "request_id"> request_id;
    Property<models::TeacherInfo, "teacher_info"> teacher_info;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру,
                           //как запрос
};
}  // namespace views::teacher::requests::approve::new_
