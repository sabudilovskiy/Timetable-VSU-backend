#include <gtest/gtest.h>
#include <concepts>
#include <openapi/all.hpp>
#include <openapi/raw/default.hpp>
#include <tuple>
#include <type_traits>
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/utest/utest.hpp>
#include <utility>

using namespace timetable_vsu_backend::openapi;

using namespace timetable_vsu_backend::openapi::types;

using namespace timetable_vsu_backend::openapi::preferences;

using namespace timetable_vsu_backend::openapi::raw;

namespace
{
struct TestClass
{
    String<Name<"test">> test;
    String<Name<"value">> value;
    auto operator<=>(const TestClass&) const = default;
};

}  // namespace

UTEST(OpenApiRaw, BasicStirngReflective)
{
    TestClass test_class;
    test_class.test() = "first";
    test_class.value() = "second";
    auto result = Raw<TestClass>::Do(test_class);
    static_assert(std::is_same_v<raw_mut_t<TestClass>, std::tuple<std::string&, std::string&>>);
    EXPECT_EQ(std::get<0>(result), "first");
    EXPECT_EQ(std::get<1>(result), "second");
    //assert refs
    EXPECT_EQ(&std::get<0>(result), &test_class.test());
    EXPECT_EQ(&std::get<1>(result), &test_class.value());
}

UTEST(OpenApiRaw, BasicArrayReflective){
    using T = Array<TestClass, Name<"some_array">>;
    T t;
    t().emplace_back(TestClass{
        .test = {"first"},
        .value = {"second"}
    });
    t().emplace_back(TestClass{
        .test = {"third"},
        .value = {"fourth"}
    });
    auto result = Raw<T>::Do(t);
    static_assert(std::is_same_v<raw_mut_t<T>, std::vector<std::tuple<std::string&, std::string&>>>);
    EXPECT_EQ(std::get<0>(result[0]), "first");
    EXPECT_EQ(std::get<1>(result[0]), "second");
    EXPECT_EQ(std::get<0>(result[1]), "third");
    EXPECT_EQ(std::get<1>(result[1]), "fourth");
    //assert refs
    EXPECT_EQ(&std::get<0>(result[0]), &t()[0].test());
    EXPECT_EQ(&std::get<1>(result[0]), &t()[0].value());
    EXPECT_EQ(&std::get<0>(result[1]), &t()[1].test());
    EXPECT_EQ(&std::get<1>(result[1]), &t()[1].value());
}

namespace {

struct TestClass2
{
    Object<TestClass, Name<"some_field">> some_field;
    Array<TestClass, Name<"some_array">> some_array;
    auto operator<=>(const TestClass2&) const = default;
};
struct SomeRequest
{
    http::Body<TestClass> body;
    http::Header<std::string, Name<"some_header">> some_header;
    http::Cookie<std::string, Name<"some_cookie">> some_cookie;
    auto operator<=>(const SomeRequest&) const = default;
};

template <size_t Head, size_t... Indexes>
decltype(auto) Get(auto&& tuple){
    auto& head = std::get<Head>(tuple);
    if constexpr (sizeof...(Indexes) != 0){
        return Get<Indexes...>(head);
    }
    else {
        return head;
    }
}

}

UTEST(OpenApiRaw, BasicRequest){
    static_assert(std::is_same_v<raw_mut_t<SomeRequest>, std::tuple<std::tuple<std::string&, std::string&>, std::string&, std::string&>>);
    SomeRequest some_req;
    auto result = Raw<SomeRequest>::Do(some_req);
    Get<0, 0>(result) = "first";
    Get<0, 1>(result) = "second";
    Get<1>(result) = "third";
    Get<2>(result) = "fourth";
    //clang-format off
    SomeRequest expected{
        .body = {TestClass{
            .test = {"first"},
            .value = {"second"}
        }},
        .some_header = {"third"},
        .some_cookie = {"fourth"}
    };
    //clang-format on
    EXPECT_EQ(some_req, expected);
}
