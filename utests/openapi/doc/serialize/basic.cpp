#include <gtest/gtest.h>

#include <boost/pfr/core.hpp>
#include <exception>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/yaml/serialize.hpp>
#include <userver/logging/log_helper.hpp>
#include <userver/utest/utest.hpp>
#include <variant>
#include <vector>

#include "openapi/base/doc.hpp"
#include "openapi/base/named_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "openapi/base/property_base.hpp"
#include "openapi/base/reflective_preferences.hpp"
#include "openapi/doc/serialize/all.hpp"
#include "openapi/types/array_type.hpp"
#include "openapi/types/object_type.hpp"
#include "openapi/types/string_type.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "utils/tests_macros.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi;
using namespace types;
using namespace preferences;

namespace user
{
struct Credentials
{
    REFLECTIVE_BASE(Credentials);
    String<Pattern<"[a-z]*">, Name<"login">> login;
    String<Name<"password">> password;
};
}  // namespace user

UTEST(TestNameStruct, Basic)
{
    EXPECT_EQ(
        timetable_vsu_backend::openapi::GetOpenApiTypeName<user::Credentials>(),
        "UserCredentials");
}

namespace server
{
struct User
{
    REFLECTIVE_BASE(User);
    Object<user::Credentials, Name<"credentials">> user;
    String<Name<"id">> id;
};
}  // namespace server

UTEST(Openapi_Doc_Serialize, MoreOneNamespace)
{
    timetable_vsu_backend::openapi::Doc doc;
    Append(doc, std::type_identity<server::User>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    auto expected_schema = RAW_STRING(
        R"(
components:
  schemas:
    ServerUser:
      type: object
      additionalProperties: false
      properties:
        credentials:
          $ref: "#/components/schemas/UserCredentials"
        id:
          type: string
      required:
        - credentials
        - id
    UserCredentials:
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

namespace timetable_vsu_backend::models
{
struct SomeStructure
{
    REFLECTIVE_BASE(SomeStructure);
    Object<server::User, Name<"user">> user;
    AdditionalProperties other;
};
}  // namespace timetable_vsu_backend::models

UTEST(Openapi_Doc_Serialize, BasicAdditionalProperties)
{
    timetable_vsu_backend::openapi::Doc doc;
    Append(doc,
           std::type_identity<timetable_vsu_backend::models::SomeStructure>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
components:
  schemas:
    TimetableVsuBackendModelsSomeStructure:
      type: object
      additionalProperties: true
      properties:
        user:
          $ref: "#/components/schemas/ServerUser"
      required:
        - user
    ServerUser:
      type: object
      additionalProperties: false
      properties:
        credentials:
          $ref: "#/components/schemas/UserCredentials"
        id:
          type: string
      required:
        - credentials
        - id
    UserCredentials:
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
