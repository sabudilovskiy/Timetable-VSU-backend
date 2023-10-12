#pragma once
#include <cstdint>
#include <utils/constexpr_string.hpp>

namespace openapi::preferences
{
template <auto value>
struct value_holder
{
    static auto constexpr kValue = value;
};

template <std::int64_t value>
struct Min : value_holder<value>
{
};

template <std::int64_t value>
struct Max : value_holder<value>
{
};

struct UniqueItems
{
};

template <utils::ConstexprString value>
struct Name : value_holder<value>
{
};

template <utils::ConstexprString value>
struct Pattern : value_holder<value>
{
};

struct UseNullOnFail
{
};

}  // namespace openapi::preferences
