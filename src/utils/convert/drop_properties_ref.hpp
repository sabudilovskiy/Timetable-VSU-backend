#pragma once
#include <concepts>
#include <optional>
#include <type_traits>

#include "base.hpp"
#include "detail/drop_properties/const_dropper_to_ref.hpp"
#include "detail/drop_properties/mut_dropper_to_ref.hpp"
namespace timetable_vsu_backend::utils::convert {
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept DroppableToTupleRef = IsConvertAll<T>;

template <typename T>
concept OptionalDroppableToTupleRef = requires {
    typename T::value_type;
    requires std::same_as<std::optional<typename T::value_type>, T>;
    requires IsConvertAll<typename T::value_type>;
};

//возвращает кортеж константных ссылок на поля структуры, где будут изначальные
//поля
template <DroppableToTupleRef T>
auto DropPropertiesToMutRefs(T& t) {
    return detail::drop_properties::MutDropperToRef<T>::Do(t);
}

//возвращает кортеж ссылок на поля структуры, где будут изначальные поля
template <OptionalDroppableToTupleRef T>
auto DropPropertiesToMutRefs(T& t) {
    using ValueType = typename std::remove_cvref_t<T>::value_type;
    using ResultTypeHelper = decltype(
        detail::drop_properties::MutDropperToRef<ValueType>::ResultType());
    using ResultType = typename ResultTypeHelper::value_type;
    std::optional<ResultType> result = std::nullopt;
    if (t) {
        result.emplace(
            detail::drop_properties::MutDropperToRef<ValueType>::Do(*t));
    }
    return result;
}

//возвращает кортеж ссылок на поля структуры, где будут изначальные поля
template <DroppableToTupleRef T>
auto DropPropertiesToConstRefs(T& t) {
    return detail::drop_properties::ConstDropperToRef<T>::Do(t);
}

//возвращает кортеж ссылок на поля структуры, где будут изначальные поля
template <OptionalDroppableToTupleRef T>
auto DropPropertiesToConstRefs(const T& t) {
    using ValueType = typename std::remove_cvref_t<T>::value_type;
    using ResultTypeHelper = decltype(
        detail::drop_properties::ConstDropperToRef<ValueType>::ResultType());
    using ResultType = typename ResultTypeHelper::value_type;
    std::optional<ResultType> result = std::nullopt;
    if (t.has_value()) {
        result.emplace(
            detail::drop_properties::ConstDropperToRef<ValueType>::Do(
                t.value()));
    }
    return result;
}

template <DroppableToTupleRef T>
using drop_properties_to_ref_const_t =
    decltype(timetable_vsu_backend::utils::convert::DropPropertiesToConstRefs(
        std::declval<const T&>()));

template <DroppableToTupleRef T>
using drop_properties_to_ref_mut_t =
    decltype(timetable_vsu_backend::utils::convert::DropPropertiesToMutRefs(
        std::declval<T&>()));

}  // namespace timetable_vsu_backend::utils::convert
