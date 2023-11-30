#pragma once
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <openapi/all.hpp>
#include <openapi/doc/base.hpp>
#include <openapi/json/parse/enum.hpp>
#include <openapi/json/serialize/enum.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>

#include "legacy/models/substring/doc.hpp"
#include "legacy/models/substring/parse.hpp"
#include "legacy/models/substring/serialize.hpp"
#include "legacy/models/substring/type.hpp"
#include "legacy/models/user_type/postgre.hpp"
#include "models/lesson_filter/type.hpp"
#include "models/lesson_v1/type.hpp"
#include "models/user/type.hpp"
#include "models/user_credentials/type.hpp"

using namespace openapi::types;
using namespace openapi::http;
using namespace openapi::preferences;
namespace views::timetable
{
struct RequestBody
{
    Optional<models::LessonFilter, Name<"filter">> filter;
    auto operator<=>(const RequestBody&) const = default;
};

struct Request
{
    Body<RequestBody> body;
    auto operator<=>(const Request&) const = default;
};

struct ResponseBody
{
    Array<models::LessonV1, Name<"lessons">> lessons;
    auto operator<=>(const ResponseBody&) const = default;
};

struct Response
{
    Body<ResponseBody> body;
    auto operator<=>(const Response&) const = default;
};

}  // namespace views::timetable
