#include "serialize.hpp"

#include <userver/formats/json/value_builder.hpp>

namespace timetable_vsu_backend::models
{
std::string Serialize(const UserType& value,
                      userver::formats::serialize::To<std::string>)
{
    switch (value)
    {
        case UserType::kUser:
            return "user";
        case UserType::kAdmin:
            return "admin";
        case UserType::kRoot:
            return "root";
        case UserType::kTeacher:
            return "teacher";
    }
}
userver::formats::json::Value Serialize(
    const UserType& value,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    std::string str =
        Serialize(value, userver::formats::serialize::To<std::string>{});
    return userver::formats::json::ValueBuilder(str).ExtractValue();
}
}  // namespace timetable_vsu_backend::models
