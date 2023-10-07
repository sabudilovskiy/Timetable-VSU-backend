#pragma once
#include "detail/parse/converter_http_request.hpp"

namespace utils::convert
{
//данный концепт лишь активирует перегрузки, но не проверяет все требования для
//типа
template <typename T>
concept HttpRequestParsable = IsConvertAll<T>&& HasTypeOfBody<T>;
}  // namespace utils::convert

namespace userver::formats::parse
{
template <::utils::convert::HttpRequestParsable T>
T Parse(const userver::server::http::HttpRequest& value, formats::parse::To<T>)
{
    T t;
    ::utils::convert::detail::parse::ConverterHttpRequest<
        T>::Do(t, value);
    return t;
}
}  // namespace userver::formats::parse
