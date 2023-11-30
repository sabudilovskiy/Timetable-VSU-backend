#include "parse.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>
#include <utils/json_type.hpp>

#include "type.hpp"

namespace legacy::models
{
// SubString Parse(const std::string& str,
// userver::formats::parse::To<SubString>)
// {
//     SubString result;
//     result.GetUnderlying().reserve(str.size() + 2);
//     result.GetUnderlying().append("%").append(str).append("%");
//     return result;
// }
SubString Parse(const userver::formats::json::Value& value,
                userver::formats::parse::To<SubString>)
{
    return SubString{value.As<std::string>()};
}
}  // namespace legacy::models
