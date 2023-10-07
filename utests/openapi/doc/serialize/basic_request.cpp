#include <openapi/all.hpp>
#include <openapi/doc/serialize/base.hpp>
#include <string_view>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/yaml/serialize.hpp>
#include <userver/utest/utest.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/tests_macros.hpp>

#include "views/hello/view.hpp"

using namespace openapi;
using namespace types;
using namespace preferences;

namespace tests
{
struct FindRequestBody
{
    String<Name<"filter">, Pattern<"[a-z]*">> filter;
    Array<int, Name<"ids">> ids;
    auto operator<=>(const FindRequestBody&) const = default;
};

struct SomeRequest
{
    http::Body<FindRequestBody> body;
    http::Header<std::string, Name<"some_header">> some_header;
    http::Cookie<std::string, Name<"some_cookie">> some_cookie;
    auto operator<=>(const SomeRequest&) const = default;
};
}  // namespace tests

UTEST(Openapi_Doc_Serialize, BasicRequest)
{
    ::openapi::Doc doc;
    auto response = doc()["requests"][GetOpenApiTypeName<tests::SomeRequest>()];
    AppendRequest(DocHelper{doc(), response},
                  std::type_identity<tests::SomeRequest>{});
    AppendRequest(DocHelper{doc(), response},
                  std::type_identity<tests::SomeRequest>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
requests:
  tests.SomeRequest:
    description: tests.SomeRequest
    requestBody:
      required: true
      content:
        application/json:
          schema:
            $ref: "#/components/schemas/tests.FindRequestBody"
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
    tests.FindRequestBody:
      type: object
      additionalProperties: false
      properties:
        filter:
          type: string
          pattern: "[a-z]*"
        ids:
          type: array
          items:
            type: integer
            format: int32
      required:
        - filter
        - ids
)"));
}
