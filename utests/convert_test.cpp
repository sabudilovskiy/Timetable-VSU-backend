#include <gtest/gtest.h>
#include <iostream>
#include <source_location>
#include <userver/formats/common/meta.hpp>
#include "../src/utils/convert/json.hpp"
#include "userver/formats/common/meta.hpp"
#include "userver/formats/json/value.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "userver/logging/log.hpp"
#include "utils/convert/base.hpp"

#include <userver/utest/utest.hpp>

namespace magic = timetable_vsu_backend::utils::convert;
struct TestStruct {
  static constexpr auto kPolicyFields = magic::PolicyFiels::ConvertAll;
  magic::Property<std::string, "login"> login;
  magic::Property<std::string, "password"> password;
};
UTEST(TestConvert, BasicJsonToStruct) {
  static_assert(magic::IsConvertAll<TestStruct>);
  static_assert(
      userver::formats::common::impl::kHasParse<userver::formats::json::Value,
                                                TestStruct>);
  userver::formats::json::ValueBuilder builder;
  builder["login"] = "test_login";
  builder["password"] = "test_password";
  auto json = builder.ExtractValue();
  auto test_struct = json.As<TestStruct>();
  EXPECT_EQ(test_struct.login.value, "test_login");
  EXPECT_EQ(test_struct.password.value, "test_password");
}

UTEST(TestConvert, BasicStructToJson) {
  static_assert(magic::IsConvertAll<TestStruct>);
  static_assert(
      userver::formats::common::impl::kHasSerialize<userver::formats::json::Value,
                                                TestStruct>);
  TestStruct test_struct;
  test_struct.login = "some_login";
  test_struct.password = "some_password";
  auto json = userver::formats::json::ValueBuilder(test_struct).ExtractValue();
  EXPECT_EQ(json["login"].As<std::string>(), "some_login");
  EXPECT_EQ(json["password"].As<std::string>(), "some_password");
}