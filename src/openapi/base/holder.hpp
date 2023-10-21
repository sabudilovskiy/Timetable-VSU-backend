#pragma once

#include <cstddef>
#include <utils/constexpr_string.hpp>
namespace openapi::traits
{
template <typename T>
struct HolderField
{
    constexpr void operator=(const T& t)
    {
        value_ = t;
        counter_changes++;
    }
    constexpr const T& operator()() const
    {
        return value_;
    }

   public:
    T value_{};
    size_t counter_changes{};
};

template <>
struct HolderField<utils::FixedString>
{
    template <size_t Size>
    constexpr void operator=(const utils::ConstexprString<Size>& t)
    {
        for (size_t index = 0; index < Size; index++)
        {
            value_[index] = t[index];
        }
        for (size_t index = Size; index < 256; index++)
        {
            value_[index] = '\0';
        }
        counter_changes++;
    }
    constexpr const utils::FixedString& operator()() const
    {
        return value_;
    }

   public:
    utils::FixedString value_{};
    size_t counter_changes{};
};

namespace detail
{
template <typename Holder, typename Option>
concept has_apply = requires(Holder& h)
{
    Apply(h, Option{});
};
template <typename Holder, typename Option>
consteval void CheckedApply(Holder& holder)
{
    static_assert(has_apply<Holder, Option>, "You use unknown option");
    Apply(holder, Option{});
}
template <typename Holder, typename... Option>
consteval void ApplyAll(Holder& holder)
{
    (CheckedApply<Holder, Option>(holder), ...);
}
}  // namespace detail

template <typename Holder, typename... Option>
consteval Holder ResolveHolder()
{
    Holder holder{};
    detail::ApplyAll<Holder, Option...>(holder);
    return holder;
}
}  // namespace openapi::traits
