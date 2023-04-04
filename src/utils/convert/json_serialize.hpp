#pragma once
#include "detail/serialize/converter_json.hpp"

namespace userver::formats::serialize {
using timetable_vsu_backend::utils::convert::IsConvertAll;
using timetable_vsu_backend::utils::convert::IsProperty;

template <IsProperty T>
json::Value Serialize(const T& t, To<json::Value>) {
  return json::ValueBuilder(t.value).ExtractValue();
}

template <IsConvertAll T>
json::Value Serialize(const T& t, To<json::Value>) {
  json::ValueBuilder json;
  timetable_vsu_backend::utils::convert::detail::serialize::ConverterJson<
      T>::Serialize(t, json);
  return json.ExtractValue();
}
}  // namespace userver::formats::serialize