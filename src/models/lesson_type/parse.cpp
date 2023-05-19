#include "parse.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>

#include "type.hpp"
#include "utils/json_type.hpp"

namespace timetable_vsu_backend::models
{
LessonType Parse(std::string_view str, userver::formats::parse::To<LessonType>)
{
    if (str == "labaratory")
    {
        return LessonType::kLabaratory;
    }
    else if (str == "lection")
    {
        return LessonType::kLection;
    }
    else if (str == "practice")
    {
        return LessonType::kPractice;
    }
    else
        throw std::runtime_error(fmt::format(
            "Fail parse LessonType, get unexpected value: {}", str));
}
LessonType Parse(const userver::formats::json::Value& value,
                 userver::formats::parse::To<LessonType>)
{
    if (!value.IsString())
    {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(std::string_view{raw_value},
                 userver::formats::parse::To<LessonType>{});
}
}  // namespace timetable_vsu_backend::models
