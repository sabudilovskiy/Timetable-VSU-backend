#include <gtest/gtest.h>

#include <boost/pfr/core.hpp>
#include <exception>
#include <openapi/all.hpp>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/yaml/serialize.hpp>
#include <userver/logging/log_helper.hpp>
#include <userver/utest/utest.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
#include <utils/tests_macros.hpp>
#include <variant>
#include <vector>

#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;
using namespace types;
using namespace preferences;

namespace tests
{
struct Credentials
{
    REFLECTIVE_BASE(Credentials);
    String<Name<"login">, Pattern<"[a-z]*">> login;
    String<Name<"password">> password;
};
}  // namespace tests

UTEST(TestNameStruct, Basic)
{
    EXPECT_EQ(timetable_vsu_backend::openapi::GetOpenApiTypeName<
                  tests::Credentials>(),
              "TestsCredentials");
}

namespace tests2
{
struct User
{
    REFLECTIVE_BASE(tests2::User);
    Object<tests::Credentials, Name<"credentials">> user;
    String<Name<"id">> id;
};
}  // namespace tests2

UTEST(Openapi_Doc_Serialize, MoreOneNamespace)
{
    timetable_vsu_backend::openapi::Doc doc;
    Append(doc, std::type_identity<tests2::User>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    auto expected_schema = RAW_STRING(
        R"(
components:
  schemas:
    Tests2User:
      type: object
      additionalProperties: false
      properties:
        credentials:
          $ref: "#/components/schemas/TestsCredentials"
        id:
          type: string
      required:
        - credentials
        - id
    TestsCredentials:
      type: object
      additionalProperties: false
      properties:
        login:
          type: string
          pattern: "[a-z]*"
        password:
          type: string
      required:
        - login
        - password
)");
    EXPECT_EQ(result_schema, expected_schema);
}

namespace timetable_vsu_backend::tests
{
struct SomeStructure
{
    REFLECTIVE_BASE(SomeStructure);
    Object<tests2::User, Name<"user">> user;
    AdditionalProperties other;
};
}  // namespace timetable_vsu_backend::tests

UTEST(Openapi_Doc_Serialize, BasicAdditionalProperties)
{
    timetable_vsu_backend::openapi::Doc doc;
    Append(doc,
           std::type_identity<timetable_vsu_backend::tests::SomeStructure>{});
    Append(doc,
           std::type_identity<timetable_vsu_backend::tests::SomeStructure>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
components:
  schemas:
    TimetableVsuBackendTestsSomeStructure:
      type: object
      additionalProperties: true
      properties:
        user:
          $ref: "#/components/schemas/Tests2User"
      required:
        - user
    Tests2User:
      type: object
      additionalProperties: false
      properties:
        credentials:
          $ref: "#/components/schemas/TestsCredentials"
        id:
          type: string
      required:
        - credentials
        - id
    TestsCredentials:
      type: object
      additionalProperties: false
      properties:
        login:
          type: string
          pattern: "[a-z]*"
        password:
          type: string
      required:
        - login
        - password
)"));
}
