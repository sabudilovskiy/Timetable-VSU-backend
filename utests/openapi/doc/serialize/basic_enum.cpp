#include <fmt/core.h>

#include <legacy/models/user_type/postgre.hpp>
#include <openapi/all.hpp>
#include <openapi/doc/base.hpp>
#include <openapi/enum/enumerator_func.hpp>
#include <openapi/json/serialize/enum.hpp>
#include <optional>
#include <type_traits>
#include <userver/formats/json/value_builder.hpp>
#include <userver/utest/utest.hpp>
#include <utils/tests_macros.hpp>
#include "openapi/enum/introspector.hpp"
#include "userver/utils/assert.hpp"

namespace test_models
{
DECLARE_OPENAPI_ENUM(UserType, int, root, teacher, user, admin, tester);
// enum struct UserType : int
// {
//     root,
//     teacher,
//     user,
//     admin,
//     tester
// };
// struct enum_introspector_UserType;
// consteval enum_introspector_UserType* get_enum_introspector(
//     std ::type_identity<UserType>)
// {
//     return nullptr;
// }
// struct enum_introspector_UserType
// {
//     using enum UserType;
//     static constexpr std::array<std::string_view, 5> names = {
//         "root", "teacher", "user", "admin", "tester"};
//     static constexpr std::array<UserType, 5> values = {root, teacher, user,
//                                                        admin, tester};
// };

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
    UASSERT(openapi::enum_introspector<test_models::UserType>::names.size() == 5);
    UASSERT(openapi::enum_introspector<test_models::UserType>::names[0] == "root");
    UASSERT(openapi::enum_introspector<test_models::UserType>::names[1] == "teacher");
    UASSERT(openapi::enum_introspector<test_models::UserType>::names[2] == "user");
    UASSERT(openapi::enum_introspector<test_models::UserType>::names[3] == "admin");
    UASSERT(openapi::enum_introspector<test_models::UserType>::names[4] == "tester");
    // constexpr userver::utils::TrivialBiMap enumerators =
    //     openapi::create_enumerator_func<test_models::UserType>();
    // static_assert(enumerators.TryFind(test_models::UserType::root) == "root");
    // static_assert(enumerators.TryFind(test_models::UserType::teacher) ==
    //               "teacher");
    // static_assert(enumerators.TryFind(test_models::UserType::user) == "user");
    // static_assert(enumerators.TryFind(test_models::UserType::admin) == "admin");
    // static_assert(enumerators.TryFind(test_models::UserType::tester) ==
    //               "tester");
    // static_assert(enumerators.TryFindICase("root") ==
    //               test_models::UserType::root);
    // static_assert(enumerators.TryFindICase("teacher") ==
    //               test_models::UserType::teacher);
    // static_assert(enumerators.TryFindICase("user") ==
    //               test_models::UserType::user);
    // static_assert(enumerators.TryFindICase("admin") ==
    //               test_models::UserType::admin);
    // static_assert(enumerators.TryFindICase("tester") ==
    //               test_models::UserType::tester);
    // static_assert(enumerators.TryFindICase("tester2") == std::nullopt);
}
