#pragma once
#include <concepts>
#include <type_traits>
#include <utils/constexpr_optional.hpp>
#include <utils/constexpr_string.hpp>

#include "property_base.hpp"

namespace timetable_vsu_backend::openapi
{
template <utils::ConstexprString Name>
struct NamedTraits
{
    static constexpr auto kName = Name;
};

namespace checks
{
template <typename T>
concept HasName = requires
{
    {
        decltype(T::kName)::kSize
    }
    ->std::convertible_to<std::size_t>;
    requires std::is_same_v<utils::ConstexprString<decltype(T::kName)::kSize>,
                            std::remove_cv_t<decltype(T::kName)>>;
    {
        T::kName
    }
    ->std::convertible_to<utils::ConstexprString<decltype(T::kName)::kSize>>;
};

template <typename T>
concept HasNotName = !HasName<T>;
}  // namespace checks

namespace details
{
template <checks::HasName T>
constexpr auto _getName()
{
    return T::kName;
}

template <checks::HasNotName T>
constexpr auto _getName()
{
    using Type = utils::ConstexprString<1>;
    return Type{""};
}
}  // namespace details

struct ConstexprSetString
{
    std::array<std::string_view, 256> test;
};

consteval ConstexprSetString foo()
{
    return {};
}

namespace traits
{
// returns ConstexprString
template <typename T>
constexpr auto GetName()
{
    return details::_getName<T>();
}

template <typename Traits>
struct NamedHelperTraits
{
    static constexpr auto name = traits::GetName<Traits>();
};
}  // namespace traits
}  // namespace timetable_vsu_backend::openapi
