#pragma once
#include "detail/parse/converter_http_request.hpp"

namespace timetable_vsu_backend::utils::convert {
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept HttpRequestParsable = IsConvertAll<T>&& HasTypeOfBody<T>;
}  // namespace timetable_vsu_backend::utils::convert

namespace userver::formats::parse {

template <timetable_vsu_backend::utils::convert::HttpRequestParsable T>
T Parse(const userver::server::http::HttpRequest& value,
        formats::parse::To<T>) {
    T t;
    timetable_vsu_backend::utils::convert::detail::parse::ConverterHttpRequest<
        T>::Parse(t, value);
    return t;
}
}  // namespace userver::formats::parse