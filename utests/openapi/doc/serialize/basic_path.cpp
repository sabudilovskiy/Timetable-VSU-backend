#include <openapi/all.hpp>
#include <openapi/http/handler.hpp>
#include <type_traits>
#include <userver/utest/utest.hpp>
#include <utils/tests_macros.hpp>

using namespace openapi;
using namespace openapi::http;
using namespace types;
using namespace preferences;

namespace tests_path
{
struct FindUserBody
{
    String<Name<"user">> user;
    String<Name<"password">> password;
    auto operator<=>(const FindUserBody&) const = default;
};
struct SomeRequest
{
    Body<FindUserBody> body;
    Header<std::string, Name<"some_header_name">> some_header;
    Header<std::string, Name<"some_another_header">> some_another_header;
    auto operator<=>(const SomeRequest&) const = default;
};
struct SomeResponse
{
    Body<FindUserBody> body;
    Header<std::string, Name<"some_header_name">> some_header;
    Header<std::string, Name<"some_another_header">> some_another_header;
    auto operator<=>(const SomeResponse&) const = default;
};
}  // namespace tests_path

UTEST(Openapi_Doc_Serialize, BasicPath)
{
    Doc doc;
    std::string path = "/login";
    std::string method = "post";
    AppendPath(doc, HandlerInfo{path, method},
               std::type_identity<tests_path::SomeRequest>{},
               std::type_identity<Resp<tests_path::SomeResponse, 200>>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
paths:
  /login:
    post:
      description: tests_path.SomeRequest
      requestBody:
        required: true
        content:
          application/json:
            schema:
              $ref: "#/components/schemas/tests_path.FindUserBody"
      parameters:
        - in: header
          name: some_header_name
          required: false
          schema:
            type: string
        - in: header
          name: some_another_header
          required: false
          schema:
            type: string
      responses:
        200:
          $ref: "#/components/responses/tests_path.SomeResponse"
components:
  schemas:
    tests_path.FindUserBody:
      type: object
      additionalProperties: false
      properties:
        user:
          type: string
        password:
          type: string
      required:
        - user
        - password
  responses:
    tests_path.SomeResponse:
      description: ""
      content:
        application/json:
          schema:
            $ref: "#/components/schemas/tests_path.FindUserBody"
      headers:
        some_header_name:
          schema:
            type: string
        some_another_header:
          schema:
            type: string
)"));
}
