#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <type_traits>
#include <userver/components/component_context.hpp>
#include <utility>

namespace utils
{
namespace details
{
template <typename T, std::size_t I>
decltype(auto) initialize_field(
    const userver::components::ComponentContext& ctx)
{
    using FieldType = boost::pfr::tuple_element_t<I, T>;
    if constexpr (std::is_pointer_v<FieldType>)
    {
        return ctx.FindComponentOptional<std::remove_pointer_t<FieldType>>();
    }
    else
    {
        return ctx.FindComponent<std::remove_cvref_t<FieldType>>();
    }
}
template <typename T, std::size_t... I>
T initialize_dependends(const userver::components::ComponentContext& ctx,
                        std::integer_sequence<std::size_t, I...>)
{
    return T{initialize_field<T, I>(ctx)...};
}
}  // namespace details
template <typename T>
T initialize_dependends(const userver::components::ComponentContext& ctx)
{
    constexpr size_t N = boost::pfr::tuple_size_v<T>;
    auto seq = std::make_index_sequence<N>{};
    return details::initialize_dependends<T>(ctx, seq);
}
}  // namespace utils
