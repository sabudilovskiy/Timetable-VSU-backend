#include "parse.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>
#include <utils/json_type.hpp>

#include "type.hpp"

namespace models
{
TimeString Parse(const std::string& str,
                 userver::formats::parse::To<TimeString>)
{
    auto value = userver::utils::datetime::GuessStringtime(str, "UTC");
    return TimeString{value};
}
TimeString Parse(const userver::formats::json::Value& value,
                 userver::formats::parse::To<TimeString>)
{
    if (!value.IsString())
    {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(raw_value, userver::formats::parse::To<TimeString>{});
}
}  // namespace models
