#pragma once
#include <concepts>
#include <optional>
#include <type_traits>
#include <utility>

namespace timetable_vsu_backend::openapi
{
struct EmptyTraits
{
};

struct Yes
{
};

namespace checks
{
template <typename T>
concept IsReflective = requires
{
    requires std::is_class_v<T>;
    typename T::Reflective;
    requires std::same_as<typename T::Reflective, Yes>;
};
};  // namespace checks

template <typename T, typename Traits = EmptyTraits>
struct PropertyBase
{
    using value_type = T;
    using traits = Traits;

    template <class Arg>
    value_type& operator=(Arg&& arg)
    {
        value = std::forward<Arg>(arg);
        return value;
    }
    value_type& operator()()
    {
        return value;
    }
    const value_type& operator()() const
    {
        return value;
    }
    value_type value;
};

template <typename T, typename Traits = EmptyTraits>
struct Property
{
};

}  // namespace timetable_vsu_backend::openapi
