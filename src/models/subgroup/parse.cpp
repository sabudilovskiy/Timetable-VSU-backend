#include "parse.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>
#include <utils/json_type.hpp>

#include "type.hpp"

namespace timetable_vsu_backend::models
{
Subgroup Parse(std::string_view str, userver::formats::parse::To<Subgroup>)
{
    if (str == "all")
    {
        return Subgroup::kAll;
    }
    else if (str == "first")
    {
        return Subgroup::kFirst;
    }
    else if (str == "second")
    {
        return Subgroup::kSecond;
    }
    else
        throw std::runtime_error(
            fmt::format("Fail parse Subgroup, get unexpected value: {}", str));
}
Subgroup Parse(const userver::formats::json::Value& value,
               userver::formats::parse::To<Subgroup>)
{
    if (!value.IsString())
    {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(raw_value, userver::formats::parse::To<Subgroup>{});
}
}  // namespace timetable_vsu_backend::models
