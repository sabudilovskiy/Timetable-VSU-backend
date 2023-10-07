#include <concepts>
#include <openapi/all.hpp>
#include <tuple>
#include <type_traits>
#include <userver/storages/postgres/io/composite_types.hpp>
#include <userver/utest/utest.hpp>
#include <utility>

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

UTEST(OpenApiToTuple, BasicStirngReflective)
{
    TestClass test_class;
    test_class.test() = "first";
    test_class.value() = "second";
    auto result = ToTuple<TestClass>::Do(test_class);
    static_assert(std::is_same_v<to_tuple_t<TestClass>, std::tuple<std::string, std::string>>);
    EXPECT_EQ(std::get<0>(result), "first");
    EXPECT_EQ(std::get<1>(result), "second");
}

UTEST(OpenApiToTuple, BasicArrayReflective){
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
    auto result = AsTuple<T>::Do(t);
    static_assert(std::is_same_v<to_tuple_t<T>, std::vector<std::tuple<std::string, std::string>>>);
    EXPECT_EQ(std::get<0>(result[0]), "first");
    EXPECT_EQ(std::get<1>(result[0]), "second");
    EXPECT_EQ(std::get<0>(result[1]), "third");
    EXPECT_EQ(std::get<1>(result[1]), "fourth");
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

UTEST(OpenApiToTuple, BasicRequest){
    static_assert(std::is_same_v<to_tuple_t<SomeRequest>, std::tuple<std::tuple<std::string, std::string>, std::string, std::string>>);
    //clang-format off
    SomeRequest some_req{
        .body = {TestClass{
            .test = {"first"},
            .value = {"second"}
        }},
        .some_header = {"third"},
        .some_cookie = {"fourth"}
    };
    //clang-format on
    auto result = ToTuple<SomeRequest>::Do(some_req);
    auto first = Get<0, 0>(result);
    auto second = Get<0, 1>(result);
    auto third = Get<1>(result);
    auto fourth = Get<2>(result);
    EXPECT_EQ(first, "first");
    EXPECT_EQ(second, "second");
    EXPECT_EQ(third, "third");
    EXPECT_EQ(fourth, "fourth");
}
