#pragma once

#include <cstddef>
#include <optional>
#include <string_view>
namespace timetable_vsu_backend::utils
{
struct AccessToNull : public std::exception
{
   public:
    AccessToNull() = default;
    virtual ~AccessToNull() = default;

    const char* what() const noexcept override
    {
        return "Attempt access to Null";
    }
};

struct Null
{
};

static constexpr Null kNull = {};

template <typename T>
struct ConstexprOptional
{
    using value_type = T;
    T value_;
    bool has_value_;
    constexpr ConstexprOptional(const T& value) noexcept
        : value_(value), has_value_(true)
    {
    }
    constexpr ConstexprOptional(Null) noexcept : value_{}, has_value_(false)
    {
    }
    constexpr bool HasValue() const noexcept
    {
        return has_value_;
    }
    constexpr bool IsNull() const noexcept
    {
        return !HasValue();
    }
    constexpr const T& get_value() const
    {
        if (!IsNull())
        {
            throw AccessToNull();
        }
        return value_;
    }
    constexpr const T& value() const
    {
        if (IsNull())
        {
            throw AccessToNull();
        }
        return value_;
    }
    constexpr T& value()
    {
        if (IsNull())
        {
            throw AccessToNull();
        }
        return value_;
    }
    constexpr ConstexprOptional& operator=(const T& t) noexcept
    {
        value_ = t;
        has_value_ = true;
        return *this;
    }
    constexpr ConstexprOptional& operator=(Null) noexcept
    {
        has_value_ = false;
        return *this;
    }
    constexpr const T& value_or(const T& t) const noexcept
    {
        if (IsNull())
        {
            return t;
        }
        else
            return value();
    }
};

}  // namespace timetable_vsu_backend::utils
