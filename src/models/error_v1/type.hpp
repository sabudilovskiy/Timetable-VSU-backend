#pragma once
#include <openapi/http/base/body.hpp>
#include <openapi/types/string_type.hpp>

namespace models
{
using namespace openapi::types;
using namespace openapi::preferences;
using namespace openapi::http;
struct ErrorV1
{
    String<Name<"machine_id">> machine_id;
    String<Name<"description">> description;
    auto operator<=>(const ErrorV1&) const = default;
};
struct ResponseErrorV1
{
    Body<ErrorV1> body;
    auto operator<=>(const ResponseErrorV1&) const = default;
};
}  // namespace models
