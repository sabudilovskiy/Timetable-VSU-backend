#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <utility>

#include "models/faculty_filter/type.hpp"
#include "utils/convert/base.hpp"
#include "utils/convert/http_request_parse.hpp"
#include "utils/convert/json_parse.hpp"
#include "utils/parse/uuid/string.hpp"
namespace timetable_vsu_backend::views::faculty::list
{
using namespace utils::convert;
struct Request
{
    OptionalProperty<models::FacultyFilter, "filter"> filter;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
};
}  // namespace timetable_vsu_backend::views::faculty::list
