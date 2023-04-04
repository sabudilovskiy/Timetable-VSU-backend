#pragma once
#include "detail/parse/converter_http_request.hpp"

namespace userver::formats::parse {

template <timetable_vsu_backend::utils::convert::IsConvertAll T>
T Parse(const userver::server::http::HttpRequest& value,
        formats::parse::To<T>) {
  T t;
  timetable_vsu_backend::utils::convert::detail::parse::ConverterHttpRequest<
      T>::Parse(t, value);
  return t;
}
}  // namespace userver::formats::parse