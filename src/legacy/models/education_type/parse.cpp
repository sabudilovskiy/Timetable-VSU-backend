#include "parse.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>
#include <utils/json_type.hpp>

#include "type.hpp"

namespace legacy::models
{
EducationType Parse(std::string_view str,
                    userver::formats::parse::To<EducationType>)
{
    if (str == "magistracy")
    {
        return EducationType::kMagistracy;
    }
    else if (str == "postgraduate")
    {
        return EducationType::kPostgraduate;
    }
    else if (str == "specialty")
    {
        return EducationType::kSpecialty;
    }
    else if (str == "undergraduate")
    {
        return EducationType::kUndergraduate;
    }
    else
        throw std::runtime_error(fmt::format(
            "Fail parse EducationType, get unexpected value: {}", str));
}
EducationType Parse(const userver::formats::json::Value& value,
                    userver::formats::parse::To<EducationType>)
{
    if (!value.IsString())
    {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(raw_value, userver::formats::parse::To<EducationType>{});
}
}  // namespace legacy::models
