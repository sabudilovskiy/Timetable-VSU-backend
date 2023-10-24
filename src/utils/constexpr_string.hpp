#pragma once
#include <algorithm>
#include <array>
#include <string_view>

namespace utils
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

using FixedString = std::array<char, 256>;

template <FixedString arr_>
auto consteval MakeConstexprString()
{
    constexpr auto real_end_it = std::find(begin(arr_), end(arr_), '\0');
    constexpr auto len = real_end_it - begin(arr_);
    char buffer[len + 1]{};
    std::copy(begin(arr_), real_end_it, std::begin(buffer));
    return utils::ConstexprString<len + 1>{buffer};
}

}  // namespace utils
