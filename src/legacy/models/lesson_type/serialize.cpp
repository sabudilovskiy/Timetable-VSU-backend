#include "serialize.hpp"

#include <userver/formats/json/value_builder.hpp>

namespace legacy::models
{
std::string Serialize(const LessonType& value,
                      userver::formats::serialize::To<std::string>)
{
    switch (value)
    {
        case LessonType::kLabaratory:
            return "labaratory";
        case LessonType::kLection:
            return "lection";
        case LessonType::kPractice:
            return "practice";
    }
}
userver::formats::json::Value Serialize(
    const LessonType& value,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    std::string str =
        Serialize(value, userver::formats::serialize::To<std::string>{});
    return userver::formats::json::ValueBuilder(str).ExtractValue();
}
}  // namespace legacy::models
