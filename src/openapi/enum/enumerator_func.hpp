#pragma once
#include <openapi/enum/declare.hpp>
#include <userver/utils/trivial_map.hpp>
#include <utility>

namespace openapi
{
namespace details
{
template <typename Selector>
struct Helper
{
    Selector selector;
    template <typename T>
    constexpr auto operator|(std::pair<std::string_view, T> p)
    {
        using R = decltype(selector.Case(p.first, p.second));
        return Helper<R>{selector.Case(p.first, p.second)};
    }
};
template <typename T, std::size_t I>
constexpr auto get_pair()
{
    constexpr auto names = ::openapi::enum_introspector<T>::names;
    constexpr auto values = ::openapi::enum_introspector<T>::values;
    return std::pair{std::get<I>(names), std::get<I>(values)};
}
template <typename T, std::size_t... I>
constexpr auto create_enumerator_helper(
    std::integer_sequence<std::size_t, I...>)
{
    return [](auto selector) {
        using Selector = decltype(selector());
        Helper<Selector> h{selector()};
        auto helper = (h | ... | get_pair<T, I>());
        return helper.selector;
    };
}
}  // namespace details
template <typename T>
requires HasIntrospector<T> constexpr auto create_enumerator_func()
{
    constexpr std::size_t N = enum_introspector<T>::names.size();
    auto seq = std::make_index_sequence<N>{};
    return details::create_enumerator_helper<T>(seq);
}

}  // namespace openapi
