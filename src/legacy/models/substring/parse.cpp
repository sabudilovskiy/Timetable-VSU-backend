#include "parse.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>
#include <utils/json_type.hpp>

#include "type.hpp"

namespace legacy::models
{
SubString Parse(const std::string& str, userver::formats::parse::To<SubString>)
{
    SubString result;
    result.GetUnderlying().reserve(str.size() + 2);
    result.GetUnderlying().append("%").append(str).append("%");
    return result;
}
SubString Parse(const userver::formats::json::Value& value,
                userver::formats::parse::To<SubString>)
{
    if (!value.IsString())
    {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(raw_value, userver::formats::parse::To<SubString>{});
}
}  // namespace legacy::models
