#include "parse.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>

#include "type.hpp"
#include "utils/json_type.hpp"

namespace timetable_vsu_backend::models {
Day Parse(std::string_view str, userver::formats::parse::To<Day>) {
    if (str == "monday") {
        return Day::kMonday;
    } else if (str == "tuesday") {
        return Day::kTuesday;
    } else if (str == "thursday") {
        return Day::kThursday;
    } else if (str == "wednesday") {
        return Day::kWednesday;
    } else if (str == "saturday") {
        return Day::kSaturday;
    } else if (str == "friday") {
        return Day::kFriday;
    } else
        throw std::runtime_error(
            fmt::format("Fail parse Day, get unexpected value: {}", str));
}
Day Parse(const userver::formats::json::Value& value,
          userver::formats::parse::To<Day>) {
    if (!value.IsString()) {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(raw_value, userver::formats::parse::To<Day>{});
}
}  // namespace timetable_vsu_backend::models
