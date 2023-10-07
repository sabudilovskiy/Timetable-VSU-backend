#include <concepts>
#include <openapi/all.hpp>
#include <tuple>
#include <type_traits>
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/utest/utest.hpp>
#include <utility>
#include "boost/pfr/core.hpp"
#include "openapi/from_tuple/default.hpp"

using namespace openapi;

using namespace openapi::types;

using namespace openapi::preferences;

using namespace openapi::raw;

namespace
{
struct TestClass
{
    String<Name<"test">> test;
    String<Name<"value">> value;
    auto operator<=>(const TestClass&) const = default;
};

}  // namespace

UTEST(OpenApiFromTuple, BasicString){
    using T = String<Name<"test">>;
    static_assert(std::is_same_v<src_t<T>, std::string>);
    std::string raw = "value";
    auto result = FromTuple<T>::Do(raw);
    EXPECT_EQ(result(), "value");
}

UTEST(OpenApiFromTuple, BasicStirngReflective)
{
    static_assert(std::is_same_v<src_t<TestClass>, std::tuple<std::string, std::string>>);
    std::tuple<std::string, std::string> tuple;
    std::get<0>(tuple) = "first";
    std::get<1>(tuple) = "second";
    auto result = FromTuple<TestClass>::Do(tuple);
    EXPECT_EQ(result.test(), "first");
    EXPECT_EQ(result.value(), "second");
}

UTEST(OpenApiFromTuple, BasicArrayReflective){
    using Raw = std::vector<std::tuple<std::string, std::string>>;
    using T = Array<TestClass, Name<"some_array">>;
    static_assert(std::is_same_v<src_t<T>, std::vector<std::tuple<std::string, std::string>>>);
    T expected;
    expected().emplace_back(TestClass{
        .test = {"first"},
        .value = {"second"}
    });
    expected().emplace_back(TestClass{
        .test = {"third"},
        .value = {"fourth"}
    });
    Raw raw;
    raw.emplace_back(std::pair{"first", "second"});
    raw.emplace_back(std::pair{"third", "fourth"});
    auto got = FromTuple<T>::Do(raw);
    ASSERT_EQ(got().size(), 2);
    EXPECT_EQ(expected()[0].test(), got()[0].test());
    EXPECT_EQ(expected()[0].value(), got()[0].value());
    EXPECT_EQ(expected()[1].test(), got()[1].test());
    EXPECT_EQ(expected()[1].value(), got()[1].value());
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

UTEST(OpenApiFromTuple, BasicRequest){
    static_assert(std::is_same_v<src_t<SomeRequest>, std::tuple<std::tuple<std::string, std::string>, std::string, std::string>>);
    std::tuple<std::tuple<std::string, std::string>, std::string, std::string> tuple{
        {"first", "second"}, "third", "fourth"
    };
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
    auto got = FromTuple<SomeRequest>::Do(tuple);
    EXPECT_EQ(expected, got);
}
