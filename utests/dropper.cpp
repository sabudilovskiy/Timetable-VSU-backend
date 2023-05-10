#include <concepts>
#include <userver/utest/utest.hpp>
#include <userver/utils/assert.hpp>
#include <utility>

#include "utils/convert/additional_properties.hpp"
#include "utils/convert/drop_properties_ref.hpp"

namespace magic = timetable_vsu_backend::utils::convert;
namespace {
struct TestStruct {
    static constexpr auto kPolicyFields = magic::PolicyFields::ConvertAll;
    magic::Property<std::string, "login"> Login;
    magic::Property<std::string, "password"> Password;
};

struct TestStruct2 {
    static constexpr auto kPolicyFields = magic::PolicyFields::ConvertAll;
    magic::Property<TestStruct, "auth"> auth;
    magic::Property<std::string, "description"> description;
};

}  // namespace

UTEST(TestDropProperties, Recursive) {
    TestStruct2 test;
    test.auth().Login() = "1232";
    test.auth().Password() = "adad";
    // UASSERT_MSG(false, "Some string");
    auto tuple = magic::DropPropertiesToMutRefs(test);
    static_assert(
        std::same_as<
            decltype(tuple),
            std::tuple<std::tuple<std::string&, std::string&>, std::string&>>);
    static_assert(std::same_as<decltype(std::get<0>(tuple)),
                               std::tuple<std::string&, std::string&>&>);
    static_assert(std::same_as<decltype(std::get<1>(tuple)), std::string&>);
    UASSERT(std::get<0>(std::get<0>(tuple)) == test.auth().Login());
    UASSERT(std::get<1>(std::get<0>(tuple)) == test.auth().Password());
    auto& left = std::get<1>(tuple);
    auto& right = test.description();
    UASSERT_MSG(std::get<1>(tuple) == test.description(),
                fmt::format("failed std::get<1>(tuple) == test.description(), "
                            "left: {}, right: {}",
                            left, right));
    UASSERT(&std::get<0>(std::get<0>(tuple)) == &test.auth().Login());
    UASSERT(&std::get<1>(std::get<0>(tuple)) == &test.auth().Password());
    UASSERT(&std::get<1>(tuple) == &test.description());
}

UTEST(TestDropProperties, Basic) {
    TestStruct test;
    test.Login() = "1232";
    test.Password() = "adad";
    auto tuple = magic::DropPropertiesToMutRefs(test);
    static_assert(std::same_as<decltype(std::get<0>(tuple)), std::string&>);
    static_assert(std::same_as<decltype(std::get<1>(tuple)), std::string&>);
    UASSERT(std::get<0>(tuple) == test.Login());
    UASSERT(std::get<1>(tuple) == test.Password());
    UASSERT(&std::get<0>(tuple) == &test.Login());
    UASSERT(&std::get<1>(tuple) == &test.Password());
}

UTEST(TestDropProperties, ConstBasic) {
    TestStruct test;
    test.Login() = "1232";
    test.Password() = "adad";
    auto tuple = magic::DropPropertiesToConstRefs(std::as_const(test));
    static_assert(
        std::same_as<decltype(std::get<0>(tuple)), const std::string&>);
    static_assert(
        std::same_as<decltype(std::get<1>(tuple)), const std::string&>);
    UASSERT(std::get<0>(tuple) == test.Login());
    UASSERT(std::get<1>(tuple) == test.Password());
    UASSERT(&std::get<0>(tuple) == &test.Login());
    UASSERT(&std::get<1>(tuple) == &test.Password());
}

UTEST(TestDropProperties, ConstRecursive) {
    TestStruct2 test;
    test.auth().Login() = "1232";
    test.auth().Password() = "adad";
    auto tuple = magic::DropPropertiesToConstRefs(std::as_const(test));
    static_assert(std::same_as<
                  decltype(tuple),
                  std::tuple<std::tuple<const std::string&, const std::string&>,
                             const std::string&>>);
    static_assert(
        std::same_as<decltype(std::get<0>(tuple)),
                     std::tuple<const std::string&, const std::string&>&>);
    static_assert(
        std::same_as<decltype(std::get<1>(tuple)), const std::string&>);
    UASSERT(std::get<0>(std::get<0>(tuple)) == test.auth().Login());
    UASSERT(std::get<1>(std::get<0>(tuple)) == test.auth().Password());
    UASSERT(test.description().empty());
    UASSERT(std::get<1>(tuple).empty());
    UASSERT(std::get<1>(tuple) == test.description());
    UASSERT(&std::get<0>(std::get<0>(tuple)) == &test.auth().Login());
    UASSERT(&std::get<1>(std::get<0>(tuple)) == &test.auth().Password());
    UASSERT(&std::get<1>(tuple) == &test.description());
}
