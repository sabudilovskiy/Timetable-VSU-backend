#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

namespace timetable_vsu_backend::utils {

template <std::size_t Size = 1>
struct ConstexprString {
    std::array<char, Size> contents{};

    constexpr ConstexprString() noexcept = default;

    constexpr ConstexprString(const char (&str)[Size]) noexcept {
        std::copy_n(str, Size, begin(contents));
    }

    constexpr operator std::string_view() const {
        return AsStringView();
    }

    constexpr std::string_view AsStringView() const {
        return {contents.begin(), contents.begin() + Size - 1};
    }

    constexpr auto c_str() const -> const char* {
        return contents.data();
    }
    friend constexpr bool operator==(const ConstexprString& string,
                                     const char* rhs) {
        std::string_view right{rhs};
        return string.AsStringView() == right;
    }
    friend constexpr bool operator==(const char* lhs,
                                     const ConstexprString& string) {
        return string == lhs;
    }
};
}  // namespace timetable_vsu_backend::utils