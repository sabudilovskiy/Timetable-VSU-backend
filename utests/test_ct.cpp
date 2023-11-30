#include <array>
#include <string>
#include <string_view>
#include <userver/utest/utest.hpp>
#include <userver/utils/assert.hpp>

namespace
{
template <std::size_t Size = 1>
struct ConstexprString
{
    static constexpr auto kSize = Size;
    std::array<char, Size> contents{};

    constexpr ConstexprString() noexcept = default;

    constexpr ConstexprString(const char (&str)[Size]) noexcept
    {
        std::copy_n(str, Size, begin(contents));
    }

    constexpr operator std::string_view() const
    {
        return AsStringView();
    }
    constexpr const char& operator[](size_t index) const
    {
        return contents[index];
    }

    constexpr char& operator[](size_t index)
    {
        return contents[index];
    }

    constexpr std::string_view AsStringView() const
    {
        return std::string_view{contents.data(), Size - 1};
    }

    std::string AsString() const
    {
        return std::string{AsStringView()};
    }

    constexpr const char* data() const
    {
        return contents.begin();
    }

    constexpr bool empty() const
    {
        return Size == 1;
    }

    constexpr auto size() const
    {
        return Size;
    }

    constexpr auto c_str() const -> const char*
    {
        return contents.data();
    }
    friend constexpr bool operator==(const ConstexprString& string,
                                     const char* rhs)
    {
        std::string_view right{rhs};
        return string.AsStringView() == right;
    }
    friend constexpr bool operator==(const char* lhs,
                                     const ConstexprString& string)
    {
        return string == lhs;
    }
};

constexpr ConstexprString<1> kEmptyString{};

template <std::size_t n>
ConstexprString(char const (&)[n]) -> ConstexprString<n>;

constexpr std::size_t k_len_fixed_string = 32;

constexpr std::pair<std::string_view, std::string_view> ParseDBName(
    std::string_view db_name)
{
    const std::size_t pos = db_name.find('.');
    if (pos == std::string_view::npos)
        return {{}, db_name};
    return {db_name.substr(0, pos), db_name.substr(pos + 1)};
}

struct DBTypeName
{
    const std::string_view schema;
    const std::string_view name;

    constexpr DBTypeName() : schema{}, name{}
    {
    }
    explicit constexpr DBTypeName(
        std::pair<std::string_view, std::string_view> n)
        : schema(n.first), name(n.second)
    {
    }
    /// Implicit constructor from a string literal, to enable declarations like
    /// @code
    /// DBTypeName my_type = "my_schema.my_type";
    /// @endcode
    /* implicit */ constexpr DBTypeName(const char* name)
        : DBTypeName(ParseDBName(name))
    {
    }
};

template <ConstexprString str>
consteval DBTypeName foo()
{
    return DBTypeName(ParseDBName(str.AsStringView()));
}

constexpr auto db_type_name = foo<"timetable_vsu.day">();

UTEST(SubStrTest, basic)
{
    ASSERT_EQ(std::string(db_type_name.schema), std::string("timetable_vsu"));
    ASSERT_EQ(std::string(db_type_name.name), std::string("day"));
}

}  // namespace
