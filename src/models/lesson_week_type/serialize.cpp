#include "serialize.hpp"

#include <userver/formats/json/value_builder.hpp>

namespace timetable_vsu_backend::models
{
std::string Serialize(const LessonWeekType& value,
                      userver::formats::serialize::To<std::string>)
{
    switch (value)
    {
        case LessonWeekType::kAll:
            return "all";
        case LessonWeekType::kEven:
            return "even";
        case LessonWeekType::kOdd:
            return "odd";
    }
}
userver::formats::json::Value Serialize(
    const LessonWeekType& value,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    std::string str =
        Serialize(value, userver::formats::serialize::To<std::string>{});
    return userver::formats::json::ValueBuilder(str).ExtractValue();
}
}  // namespace timetable_vsu_backend::models
