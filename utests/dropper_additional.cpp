#include <concepts>
#include <optional>
#include <userver/utest/utest.hpp>
#include <userver/utils/assert.hpp>
#include <utility>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/drop_properties_ref.hpp>

using namespace timetable_vsu_backend::utils::convert;
namespace
{
struct TestStruct
{
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    Property<std::string, "login"> login;
    Property<std::string, "password"> password;
};

struct TestStruct2
{
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    Property<int, "descriptor"> descriptor;
    Property<int, "money"> money;
};

struct TestStruct3
{
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    OptionalProperty<TestStruct, "auth"> auth;
    OptionalProperty<TestStruct2, "description"> description;
};
}  // namespace

UTEST(TestDropAdditionalProperties, Recursive)
{
    TestStruct3 test;
    test.description() = {TestStruct2{.descriptor = {42}, .money = {43}}};
    auto tuple = DropPropertiesToMutRefs(test);
    auto& [_, o2] = test;
    auto& [o3, o4] = *o2();
    auto& [t1, t2] = tuple;
    using Type1 = decltype(t1);
    static_assert(
        std::same_as<Type1,
                     std::optional<std::tuple<std::string&, std::string&>>>);
    using Type2 = decltype(t2);
    static_assert(std::same_as<Type2, std::optional<std::tuple<int&, int&>>>);
    UASSERT(!t1);
    UASSERT(t2);
    auto& [t3, t4] = *t2;
    UASSERT(&t3 == &o3());
    UASSERT(&t4 == &o4());
}
