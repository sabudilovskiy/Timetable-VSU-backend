#pragma once
#include "detail/parse/converter_json.hpp"

namespace userver::formats::parse {
using timetable_vsu_backend::utils::convert::IsConvertAll;
using timetable_vsu_backend::utils::convert::IsProperty;

template <IsProperty T>
T Parse(const json::Value& value, To<T>) {
  return T{value.As<typename T::value_type>()};
}

template <IsConvertAll T>
T Parse(const json::Value& value, To<T>) {
  T t;
  timetable_vsu_backend::utils::convert::detail::parse::ConverterJson<T>::Parse(
      t, value);
  return t;
}

}  // namespace userver::formats::parse