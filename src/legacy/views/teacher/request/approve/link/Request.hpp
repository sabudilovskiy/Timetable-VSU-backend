#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <utility>
#include <utils/convert/base.hpp>
#include <utils/convert/http_request_parse.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/parse/uuid/string.hpp>
namespace legacy::views::teacher::requests::approve::link
{
using namespace utils::convert;
struct Request
{
    HeaderProperty<boost::uuids::uuid, "token"> token;
    Property<boost::uuids::uuid, "teacher_id"> teacher_id;
    Property<boost::uuids::uuid, "request_id"> request_id;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
};
}  // namespace legacy::views::teacher::requests::approve::link
