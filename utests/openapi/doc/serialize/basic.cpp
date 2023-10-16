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

using namespace openapi;
using namespace types;
using namespace preferences;

namespace tests
{
struct Credentials
{
    String<Name<"login">, Pattern<"[a-z]*">> login;
    String<Name<"password">> password;
    auto operator<=>(const Credentials&) const = default;
};
}  // namespace tests

UTEST(TestNameStruct, Basic)
{
    EXPECT_EQ(::openapi::GetOpenApiTypeName<tests::Credentials>(),
              "tests.Credentials");
}

namespace tests2
{
struct User
{
    Object<tests::Credentials, Name<"credentials">> user;
    String<Name<"id">> id;
    auto operator<=>(const tests2::User&) const = default;
};
}  // namespace tests2

UTEST(Openapi_Doc_Serialize, MoreOneNamespace)
{
    ::openapi::Doc doc;
    Append(doc, std::type_identity<tests2::User>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    auto expected_schema = RAW_STRING(
        R"(
components:
  schemas:
    tests2.User:
      type: object
      additionalProperties: false
      properties:
        credentials:
          $ref: "#/components/schemas/tests.Credentials"
        id:
          type: string
      required:
        - credentials
        - id
    tests.Credentials:
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

namespace tests
{
struct SomeStructure
{
    auto operator<=>(const SomeStructure&) const = default;
    Object<tests2::User, Name<"user">> user;
    AdditionalProperties other;
};
}  // namespace tests

UTEST(Openapi_Doc_Serialize, BasicAdditionalProperties)
{
    ::openapi::Doc doc;
    Append(doc, std::type_identity<::tests::SomeStructure>{});
    Append(doc, std::type_identity<::tests::SomeStructure>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
components:
  schemas:
    tests.SomeStructure:
      type: object
      additionalProperties: true
      properties:
        user:
          $ref: "#/components/schemas/tests2.User"
      required:
        - user
    tests2.User:
      type: object
      additionalProperties: false
      properties:
        credentials:
          $ref: "#/components/schemas/tests.Credentials"
        id:
          type: string
      required:
        - credentials
        - id
    tests.Credentials:
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
