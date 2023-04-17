#include "serialize.hpp"

#include <userver/formats/json/value_builder.hpp>

namespace timetable_vsu_backend::models {
std::string Serialize(const Subgroup& value,
                      userver::formats::serialize::To<std::string>) {
    switch (value) {
        case Subgroup::kAll:
            return "all";
        case Subgroup::kFirst:
            return "first";
        case Subgroup::kSecond:
            return "second";
    }
}
userver::formats::json::Value Serialize(
    const Subgroup& value,
    userver::formats::serialize::To<userver::formats::json::Value>) {
    std::string str =
        Serialize(value, userver::formats::serialize::To<std::string>{});
    return userver::formats::json::ValueBuilder(str).ExtractValue();
}
}  // namespace timetable_vsu_backend::models