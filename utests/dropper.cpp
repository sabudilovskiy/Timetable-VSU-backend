#include "userver/utils/assert.hpp"
#include "utils/convert/drop_properties.hpp"
#include <concepts>
#include <userver/utest/utest.hpp>

namespace magic = timetable_vsu_backend::utils::convert;
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

UTEST(TestDropProperties, Recursive){
    TestStruct2 test;
    test.auth().Login() = "1232";
    test.auth().Password() = "adad";
    auto tuple = magic::DropPropertiesToRefs(test);
    static_assert(std::same_as<decltype(std::get<0>(tuple)), std::tuple<std::string&, std::string&>&>);
    static_assert(std::same_as<decltype(std::get<1>(tuple)), std::string&>);
    UASSERT(std::get<0>(std::get<0>(tuple)) == test.auth().Login());
    UASSERT(std::get<1>(std::get<0>(tuple)) == test.auth().Password());
    UASSERT(std::get<1>(tuple) == test.description());
    UASSERT(&std::get<0>(std::get<0>(tuple)) == &test.auth().Login());
    UASSERT(&std::get<1>(std::get<0>(tuple)) == &test.auth().Password());
    UASSERT(&std::get<1>(tuple) == &test.description());
}

UTEST(TestDropProperties, Basic){
    TestStruct test;
    test.Login() = "1232";
    test.Password() = "adad";
    auto tuple = magic::DropPropertiesToRefs(test);
    static_assert(std::same_as<decltype(std::get<0>(tuple)), std::string&>);
    static_assert(std::same_as<decltype(std::get<1>(tuple)), std::string&>);
    UASSERT(std::get<0>(tuple) == test.Login());
    UASSERT(std::get<1>(tuple) == test.Password());
    UASSERT(&std::get<0>(tuple) == &test.Login());
    UASSERT(&std::get<1>(tuple) == &test.Password());
}
