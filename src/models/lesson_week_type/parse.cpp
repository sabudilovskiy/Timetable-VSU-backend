#include "parse.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>

#include "type.hpp"
#include "utils/json_type.hpp"

namespace timetable_vsu_backend::models {
LessonWeekType Parse(std::string_view str,
                     userver::formats::parse::To<LessonWeekType>) {
    if (str == "all") {
        return LessonWeekType::kAll;
    } else if (str == "even") {
        return LessonWeekType::kEven;
    } else if (str == "odd") {
        return LessonWeekType::kOdd;
    } else
        throw std::runtime_error(fmt::format(
            "Fail parse LessonWeekType, get unexpected value: {}", str));
}
LessonWeekType Parse(const userver::formats::json::Value& value,
                     userver::formats::parse::To<LessonWeekType>) {
    if (!value.IsString()) {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(raw_value, userver::formats::parse::To<LessonWeekType>{});
}
}  // namespace timetable_vsu_backend::models
