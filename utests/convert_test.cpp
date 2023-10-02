#include <gtest/gtest.h>

#include <iostream>
#include <source_location>
#include <userver/formats/common/meta.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/http/http_request.hpp>
#include <userver/utest/utest.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/convert/json_serialize.hpp>

namespace magic = timetable_vsu_backend::utils::convert;
struct TestStruct
{
    static constexpr auto kPolicyFields = magic::PolicyFields::ConvertAll;
    magic::Property<std::string, "login"> Login;
    magic::Property<std::string, "password"> Password;
};
static_assert(magic::IsProperty<decltype(TestStruct::Login)>);

UTEST(TestConvert, BasicJsonToStruct)
{
    static_assert(magic::IsConvertAll<TestStruct>);
    static_assert(
        userver::formats::common::impl::kHasParse<userver::formats::json::Value,
                                                  TestStruct>);
    userver::formats::json::ValueBuilder builder;
    builder["login"] = "test_login";
    builder["password"] = "test_password";
    auto json = builder.ExtractValue();
    auto test_struct = json.As<TestStruct>();
    EXPECT_EQ(test_struct.Login(), "test_login");
    EXPECT_EQ(test_struct.Password(), "test_password");
}

UTEST(TestConvert, BasicStructToJson)
{
    static_assert(magic::IsConvertAll<TestStruct>);
    static_assert(userver::formats::common::impl::kHasSerialize<
                  userver::formats::json::Value, TestStruct>);
    TestStruct test_struct;
    test_struct.Login() = "some_login";
    test_struct.Password() = "some_password";
    auto json =
        userver::formats::json::ValueBuilder(test_struct).ExtractValue();
    EXPECT_EQ(json["login"].As<std::string>(), "some_login");
    EXPECT_EQ(json["password"].As<std::string>(), "some_password");
}
