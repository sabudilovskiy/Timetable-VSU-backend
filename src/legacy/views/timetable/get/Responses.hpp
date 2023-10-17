#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/http_response_serialize.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/convert/json_serialize.hpp>

#include "http/ErrorV1.hpp"
#include "legacy/models/lesson_v1/type.hpp"
#include "legacy/models/user_type/serialize.hpp"
#include "legacy/models/user_type/type.hpp"

namespace legacy::views::timetable::get
{
using namespace utils::convert;
struct Response200
{
    ArrayProperty<legacy::models::LessonV1, "lessons"> lessons;
    static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Json;
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
    static constexpr userver::server::http::HttpStatus kStatusCode =
        userver::server::http::HttpStatus::kOk;
};

static_assert(userver::formats::common::impl::kHasSerialize<
              userver::formats::json::Value, legacy::models::LessonV1>);
static_assert(
    userver::formats::common::impl::kHasSerialize<
        userver::formats::json::Value, std::vector<legacy::models::LessonV1>>);

}  // namespace legacy::views::timetable::get
