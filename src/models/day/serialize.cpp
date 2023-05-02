#include "serialize.hpp"

#include <userver/formats/json/value_builder.hpp>

namespace timetable_vsu_backend::models {
std::string Serialize(const Day& value,
                      userver::formats::serialize::To<std::string>) {
    switch (value) {
        case Day::kMonday:
            return "monday";
        case Day::kTuesday:
            return "tuesday";
        case Day::kWednesday:
            return "wednesday";
        case Day::kThursday:
            return "thursday";
        case Day::kFriday:
            return "friday";
        case Day::kSaturday:
            return "saturday";
    }
}
userver::formats::json::Value Serialize(
    const Day& value,
    userver::formats::serialize::To<userver::formats::json::Value>) {
    std::string str =
        Serialize(value, userver::formats::serialize::To<std::string>{});
    return userver::formats::json::ValueBuilder(str).ExtractValue();
}
}  // namespace timetable_vsu_backend::models
