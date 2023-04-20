#pragma once
#include "base.hpp"
#include "detail/drop_properties/dropper_to_ref.hpp"
namespace timetable_vsu_backend::utils::convert {
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept Convertable = IsConvertAll<T>;
//возвращает кортеж ссылок на поля структуры, где будут изначальные поля
template <Convertable T>
auto DropPropertiesToRefs(T& t) {
    return detail::drop_properties::DropperToRef<T>::Do(t);
}
}  // namespace timetable_vsu_backend::utils::convert