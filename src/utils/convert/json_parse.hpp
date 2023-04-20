#pragma once
#include "detail/parse/converter_json.hpp"
#include "userver/compiler/demangle.hpp"
#include "userver/logging/log.hpp"

namespace timetable_vsu_backend::utils::convert {
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept JsonParsable = IsConvertAll<T>;
}  // namespace timetable_vsu_backend::utils::convert

namespace userver::formats::parse {

template <timetable_vsu_backend::utils::convert::IsProperty T>
T Parse(const json::Value& value, To<T>) {
    return T{value.As<typename T::value_type>()};
}

template <timetable_vsu_backend::utils::convert::JsonParsable T>
T Parse(const json::Value& value, To<T>) {
    T t;
    timetable_vsu_backend::utils::convert::detail::parse::ConverterJson<
        T>::Parse(t, value);
    return t;
}

}  // namespace userver::formats::parse