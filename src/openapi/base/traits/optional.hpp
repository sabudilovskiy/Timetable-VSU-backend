#pragma once

#include <openapi/base/named_traits.hpp>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>
namespace openapi
{
namespace checks
{
template <typename T>
concept HasUseNullOnFail = requires
{
    {
        T::kUseNullOnFail
    }
    ->std::convertible_to<utils::ConstexprOptional<bool>>;
};

}  // namespace checks

namespace detail
{
template <typename T>
requires checks::HasUseNullOnFail<T> constexpr utils::ConstexprOptional<bool>
_getUseNullOnFail()
{
    return T::kUseNullOnFail;
}

template <typename T>
requires(!checks::HasUseNullOnFail<T>) constexpr utils::ConstexprOptional<
    bool> _getUseNullOnFail()
{
    return utils::kNull;
}

}  // namespace detail

namespace traits
{
template <typename T>
constexpr utils::ConstexprOptional<bool> GetUseNullOnFail()
{
    return detail::_getUseNullOnFail<T>();
}

template <typename Traits>
struct OptionalHelperTraits : NamedHelperTraits<Traits>
{
    static constexpr utils::ConstexprOptional<bool> null_on_failure =
        traits::GetUseNullOnFail<Traits>();
    constexpr OptionalHelperTraits()
    {
    }
};

}  // namespace traits
}  // namespace openapi
