#include <gtest/gtest.h>

#include <boost/pfr/core.hpp>
#include <exception>
#include <openapi/base/doc.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/preferences.hpp>
#include <openapi/base/property_base.hpp>
#include <openapi/base/reflective_preferences.hpp>
#include <openapi/doc/serialize/all.hpp>
#include <openapi/http/base/body.hpp>
#include <openapi/http/base/cookie.hpp>
#include <openapi/http/base/header.hpp>
#include <openapi/http/base/response_property.hpp>
#include <openapi/types/all.hpp>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/yaml/serialize.hpp>
#include <userver/logging/log_helper.hpp>
#include <userver/utest/utest.hpp>
#include <variant>
#include <vector>

#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "utils/tests_macros.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;
using namespace types;
using namespace preferences;

namespace models
{
struct FindRequestBody
{
    REFLECTIVE_BASE(FindRequestBody);
    String<Name<"filter">, Pattern<"[a-z]*">> filter;
    Array<int, Name<"ids">> ids;
};

struct SomeRequest
{
    REFLECTIVE_BASE(SomeRequest);
    http::Body<FindRequestBody> body;
    http::Header<std::string, Name<"some_header">> some_header;
    http::Cookie<std::string, Name<"some_cookie">> some_cookie;
};
}  // namespace models

UTEST(Openapi_Doc_Serialize, BasicRequest)
{
    timetable_vsu_backend::openapi::Doc doc;
    AppendRequest(doc, std::type_identity<models::SomeRequest>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    std::clog << '\n' << result_schema << '\n';
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
requests:
  ModelsSomeRequest:
    requestBody:
      required: false
      content:
        application/json:
          schema:
            $ref: "#/components/schemas/ModelsFindRequestBody"
    parameters:
      - in: header
        name: some_header
        required: false
        schema:
          type: string
      - in: cookie
        name: some_cookie
        required: false
        schema:
          type: string
components:
  schemas:
    ModelsFindRequestBody:
      type: object
      additionalProperties: false
      properties:
        filter:
          type: string
          pattern: "[a-z]*"
        ids:
          type: array
          items:
            type: Integer
            format: int32
      required:
        - filter
        - ids
)"));
}
