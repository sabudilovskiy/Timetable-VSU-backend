#include <openapi/all.hpp>
#include <openapi/http/serialize/response.hpp>
#include <userver/utest/utest.hpp>
#include <utils/tests_macros.hpp>

using namespace timetable_vsu_backend::openapi;
using namespace timetable_vsu_backend::openapi::http;
using namespace types;
using namespace preferences;

namespace tests
{
struct FindUserBody
{
    String<Name<"user">> user;
    String<Name<"password">> password;
    auto operator<=>(const FindUserBody&) const = default;
};
struct SomeResponse
{
    Body<FindUserBody> body;
    Header<std::string, Name<"some_header_name">> some_header;
    Header<std::string, Name<"some_another_header">> some_another_header;
    auto operator<=>(const SomeResponse&) const = default;
};
}  // namespace tests

UTEST(Openapi_Doc_Serialize, BasicResponse)
{
    Doc doc;
    AppendResponse(doc, std::type_identity<tests::SomeResponse>{});
    AppendResponse(doc, std::type_identity<tests::SomeResponse>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
components:
  responses:
    TestsSomeResponse:
      content:
        application/json:
          schema:
            $ref: "#/components/schemas/TestsFindUserBody"
      headers:
        some_header_name:
          schema:
            type: string
        some_another_header:
          schema:
            type: string
  schemas:
    TestsFindUserBody:
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
)"));
}
