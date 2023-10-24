#include <fmt/core.h>

#include <legacy/models/user_type/postgre.hpp>
#include <openapi/all.hpp>
#include <openapi/base/enum/enumerator_func.hpp>
#include <openapi/doc/base.hpp>
#include <openapi/json/serialize/enum.hpp>
#include <optional>
#include <type_traits>
#include <userver/utest/utest.hpp>
#include <utils/tests_macros.hpp>
#include "userver/formats/json/value_builder.hpp"

namespace test_models
{
DECLARE_OPENAPI_ENUM(UserType, int, root, teacher, user, admin, tester);

}  // namespace test_models

UTEST(OpenApiDoc, BasicEnum)
{
    ::openapi::Doc doc;
    Append(openapi::DocHelper{doc.value_, doc.value_},
           std::type_identity<test_models::UserType>{});
    auto value = doc().ExtractValue();
    auto result_schema = ToString(value);
    EXPECT_EQ(result_schema, RAW_STRING(
                                 R"(
components:
  schemas:
    test_models.UserType:
      type: string
      enum:
        - root
        - teacher
        - user
        - admin
        - tester
)"));
}

UTEST(OpenApiDoc, BasicEnumerator)
{
    constexpr userver::utils::TrivialBiMap enumerators =
        openapi::create_enumerator_func<test_models::UserType>();
    static_assert(enumerators.TryFind(test_models::UserType::root) == "root");
    static_assert(enumerators.TryFind(test_models::UserType::teacher) ==
                  "teacher");
    static_assert(enumerators.TryFind(test_models::UserType::user) == "user");
    static_assert(enumerators.TryFind(test_models::UserType::admin) == "admin");
    static_assert(enumerators.TryFind(test_models::UserType::tester) ==
                  "tester");
    static_assert(enumerators.TryFindICase("root") ==
                  test_models::UserType::root);
    static_assert(enumerators.TryFindICase("teacher") ==
                  test_models::UserType::teacher);
    static_assert(enumerators.TryFindICase("user") ==
                  test_models::UserType::user);
    static_assert(enumerators.TryFindICase("admin") ==
                  test_models::UserType::admin);
    static_assert(enumerators.TryFindICase("tester") ==
                  test_models::UserType::tester);
    static_assert(enumerators.TryFindICase("tester2") == std::nullopt);
}
