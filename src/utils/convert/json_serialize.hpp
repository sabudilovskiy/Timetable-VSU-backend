#pragma once
#include <utils/convert/base.hpp>

#include "detail/serialize/converter_json.hpp"

namespace utils::convert
{
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept JsonSeriazable = IsConvertAll<T>;
}  // namespace utils::convert

namespace userver::formats::serialize
{
template <::utils::convert::IsProperty T>
json::Value Serialize(const T& t, To<json::Value>)
{
    return json::ValueBuilder(t.value).ExtractValue();
}

template <::utils::convert::JsonSeriazable T>
json::Value Serialize(const T& t, To<json::Value>)
{
    json::ValueBuilder json;
    ::utils::convert::detail::serialize::ConverterJson<
        T>::Do(t, json);
    return json.ExtractValue();
}
}  // namespace userver::formats::serialize
