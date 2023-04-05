#pragma once
#include "detail/serialize/converter_http_response.hpp"

namespace timetable_vsu_backend::utils::convert {
//данынй концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept HttpResponseSeriazable =
    IsConvertAll<T> && HasTypeOfBody<T> && HasStatusCode<T>;

template <HttpResponseSeriazable T>
void Serialize(const T& t, HttpResponse& response) {
    detail::serialize::ConverterHttpResponse<T>::Serialize(t, response);
}
}  // namespace timetable_vsu_backend::utils::convert