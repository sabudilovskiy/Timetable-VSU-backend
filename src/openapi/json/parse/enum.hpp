#pragma once

#include <openapi/base/enum/string.hpp>
#include <stdexcept>
#include <userver/formats/json/value.hpp>
#include <userver/logging/log.hpp>
#include <utils/formated_exception.hpp>

namespace userver::formats::parse
{
template <typename T>
requires openapi::HasIntrospector<T> T Parse(const json::Value& item, To<T>)
{
    using namespace openapi;

    auto result = item.As<std::string>();
    std::optional<T> parsed = from_string_view<T>(result);
    if (!parsed)
    {
        throw ::utils::formated_exception("Can't parse {} to enum value",
                                          result);
    }
    else
        return parsed.value();
}
}  // namespace userver::formats::parse
