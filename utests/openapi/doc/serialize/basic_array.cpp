#include <gtest/gtest.h>

#include <exception>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/utest/utest.hpp>
#include <variant>
#include <vector>

#include "boost/pfr/core.hpp"
#include "openapi/base/doc.hpp"
#include "openapi/base/named_traits.hpp"
#include "openapi/base/preferences.hpp"
#include "openapi/base/property_base.hpp"
#include "openapi/doc/serialize/all.hpp"
#include "openapi/types/array_type.hpp"
#include "openapi/types/object_type.hpp"
#include "openapi/types/string_type.hpp"
#include "userver/formats/yaml/serialize.hpp"
#include "userver/logging/log_helper.hpp"
#include "utils/constexpr_optional.hpp"
#include "utils/constexpr_string.hpp"
#include "utils/tests_macros.hpp"
#include "views/hello/view.hpp"

using namespace timetable_vsu_backend::openapi::types;
using namespace timetable_vsu_backend::openapi::preferences;

namespace user
{
struct Credentials
{
    using Reflective = timetable_vsu_backend::openapi::Yes;
    String<Pattern<"[a-z]*">, Name<"login">> login;
    String<Name<"password">> password;
};
}  // namespace user

namespace server
{
struct User
{
    using Reflective = timetable_vsu_backend::openapi::Yes;
    Object<user::Credentials, Name<"user">> user;
    String<Name<"id">> id;
};
}  // namespace server

UTEST(TestNameStruct, Basic)
{
    EXPECT_EQ(
        timetable_vsu_backend::openapi::GetOpenApiTypeName<user::Credentials>(),
        "UserCredentials");
}

UTEST(Openapi_Doc_Serialize, BasicArray)
{
    timetable_vsu_backend::openapi::Doc doc;
    Append(doc, std::type_identity<server::User>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
R"(
components:
  schemas:
    ServerUser:
      type: object
      additionalProperties: false
      properties:
        user: $ref/components/schemas/UserCredentials
        id:
          type: string
      required:
        - user
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
)"
));
}

UTEST(MacrosRawString, Basic)
{
  auto string = RAW_STRING(
R"(
test
)");
  EXPECT_EQ(string, "test");
}
