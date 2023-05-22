#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <utility>

#include "models/teacher_filter/type.hpp"
#include "utils/convert/base.hpp"
#include "utils/convert/http_request_parse.hpp"
#include "utils/convert/json_parse.hpp"
#include "utils/parse/uuid/string.hpp"
namespace timetable_vsu_backend::views::teacher::requests::list
{
using namespace utils::convert;
struct Request
{
    HeaderProperty<boost::uuids::uuid, "token"> token;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Empty;  //открываем возможность использовать структуру, как
                            //запрос
};
}  // namespace timetable_vsu_backend::views::teacher::requests::list
