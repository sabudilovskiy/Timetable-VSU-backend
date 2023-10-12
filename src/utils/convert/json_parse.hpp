#pragma once
#include <userver/compiler/demangle.hpp>
#include <userver/logging/log.hpp>

#include "detail/parse/converter_json.hpp"

namespace utils::convert
{
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept JsonParsable = IsConvertAll<T>;
}  // namespace utils::convert

namespace userver::formats::parse
{
template <::utils::convert::IsProperty T>
T Parse(const json::Value& value, To<T>)
{
    return T{value.As<typename T::value_type>()};
}

template <::utils::convert::JsonParsable T>
T Parse(const json::Value& value, To<T>)
{
    T t;
    ::utils::convert::detail::parse::ConverterJson<T>::Do(t, value);
    return t;
}

}  // namespace userver::formats::parse
