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
struct TestClass2
{
    Object<TestClass, Name<"some_field">> some_field;
    Array<TestClass, Name<"some_array">> some_array;
};
struct SomeRequest
{
    http::Body<TestClass> body;
    http::Header<std::string, Name<"some_header">> some_header;
    http::Cookie<std::string, Name<"some_cookie">> some_cookie;
    auto operator<=>(const SomeRequest&) const = default;
};
}  // namespace

UTEST(OpenApiRaw, BasicReflective)
{
    using namespace std::literals;

    using TestArray = Array<TestClass, Name<"some_array">>;
    using TestArrayRaw = raw_mut_t<TestArray>;
    static_assert(std::same_as<TestArrayRaw, std::vector<std::tuple<std::basic_string<char> &, std::basic_string<char> &>>>);

    using Test1 = raw_mut_t<String<Name<"value">>>;
    static_assert(std::same_as<Test1, std::string&>);

    using Test2 = raw_mut_t<TestClass>;
    static_assert(std::same_as<Test2, std::tuple<std::string&, std::string&>>);

    // using Test3 = Object<TestClass, Name<"some_field">>;
    // using Test4 = raw_mut_t<Test3>;
    // static_assert(std::same_as<Test4, std::tuple<std::string&, std::string&>>);

    // using Test5 = raw_mut_t<TestClass2>;
    // static_assert(std::same_as<Test5, std::tuple<Test2, std::vector<Test2>>>);

    // using Test6 = raw_mut_t<SomeRequest>;
    // static_assert(std::same_as<Test6, std::tuple<Test4, std::string&, std::string&>>);
    // SomeRequest req;
    // req.some_cookie() = "cookie";
    // req.some_header() = "header";
    // req.body().test() = "test3232";
    // req.body().value() = "value1312";
    // auto val = Raw<SomeRequest>::Do(req);
    // EXPECT_EQ(val, std::make_tuple(std::make_tuple("test3232"s, "value1312"s), "header", "cookie"));
}
