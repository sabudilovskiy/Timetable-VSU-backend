#pragma once
#include <boost/pfr.hpp>
#include <cstddef>
#include <openapi/base/object_property.hpp>
#include <openapi/base/property_base.hpp>
#include <tuple>
#include <type_traits>
#include <userver/storages/postgres/io/composite_types.hpp>
#include <utility>

namespace openapi
{
namespace impl
{
template <typename T, std::size_t... I>
requires checks::is_reflective_v<T> auto MakeTypeTupleHelper(
    std::type_identity<T>, std::integer_sequence<size_t, I...>)
{
    using Type =
        std::tuple<std::remove_cvref_t<boost::pfr::tuple_element_t<I, T>>...>;
    return std::type_identity<Type>{};
}
}  // namespace impl
template <typename T>
requires checks::is_reflective_v<T> auto MakeSequence()
{
    return std::make_index_sequence<boost::pfr::tuple_size<T>::value>();
}

/*
Возвращает std::type_identity<std::tuple<Field...>

Используйте для быстрого разбинда рефлективных структур в вариадик пак
*/
template <typename T>
requires checks::is_reflective_v<T> auto MakeTypeTuple()
{
    auto seq = MakeSequence<T>();
    return impl::MakeTypeTupleHelper(std::type_identity<T>{}, seq);
}

namespace impl
{
/*

*/
template <typename Callable, typename... Fields>
void CallAllFields(Callable&& callable,
                   std::type_identity<std::tuple<Fields...>>)
{
    (callable(std::type_identity<Fields>{}), ...);
}
}  // namespace impl
/*
Применяется Callable к каждому полю

Callable должна принимать std::type_identity<T>
*/
template <typename T, typename Callable>
requires checks::is_reflective_v<T> void CallAllFields(Callable&& callable)
{
    auto tuple_identity = MakeTypeTuple<T>();
    impl::CallAllFields(std::forward<Callable>(callable), tuple_identity);
}
}  // namespace openapi
