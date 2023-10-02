#include <openapi/all.hpp>
#include <string_view>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/yaml/serialize.hpp>
#include <userver/utest/utest.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/tests_macros.hpp>

#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;
using namespace types;
using namespace preferences;

namespace tests
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
}  // namespace tests

UTEST(Openapi_Doc_Serialize, BasicRequest)
{
    timetable_vsu_backend::openapi::Doc doc;
    AppendRequest(doc, std::type_identity<tests::SomeRequest>{});
    AppendRequest(doc, std::type_identity<tests::SomeRequest>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
requests:
  TestsSomeRequest:
    requestBody:
      required: false
      content:
        application/json:
          schema:
            $ref: "#/components/schemas/TestsFindRequestBody"
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
    TestsFindRequestBody:
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
