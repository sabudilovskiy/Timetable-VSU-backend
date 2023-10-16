#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <utility>
#include <utils/convert/base.hpp>
#include <utils/convert/http_request_parse.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/parse/uuid/string.hpp>

#include "legacy/models/group_stage_filter/type.hpp"
namespace legacy::views::group::stage::list
{
using namespace utils::convert;
struct Request
{
    OptionalProperty<legacy::models::GroupStageFilter, "filter"> filter;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
};
}  // namespace legacy::views::group::stage::list
