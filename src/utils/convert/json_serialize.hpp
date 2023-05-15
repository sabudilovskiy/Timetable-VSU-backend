#pragma once
#include "detail/serialize/converter_json.hpp"
#include "utils/convert/base.hpp"

namespace timetable_vsu_backend::utils::convert {
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept JsonSeriazable = IsConvertAll<T>;
}  // namespace timetable_vsu_backend::utils::convert

namespace userver::formats::serialize {

template <timetable_vsu_backend::utils::convert::IsProperty T>
json::Value Serialize(const T& t, To<json::Value>) {
    return json::ValueBuilder(t.value).ExtractValue();
}

template <timetable_vsu_backend::utils::convert::JsonSeriazable T>
json::Value Serialize(const T& t, To<json::Value>) {
    json::ValueBuilder json;
    timetable_vsu_backend::utils::convert::detail::serialize::ConverterJson<
        T>::Do(t, json);
    return json.ExtractValue();
}
}  // namespace userver::formats::serialize
