#include "parse.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <userver/formats/json.hpp>

#include "type.hpp"
#include "utils/json_type.hpp"

namespace timetable_vsu_backend::models
{
UserType Parse(std::string_view str, userver::formats::parse::To<UserType>)
{
    if (str == "user")
    {
        return UserType::kUser;
    }
    else if (str == "root")
    {
        return UserType::kRoot;
    }
    else if (str == "admin")
    {
        return UserType::kAdmin;
    }
    else if (str == "teacher")
    {
        return UserType::kTeacher;
    }
    else
        throw std::runtime_error(
            fmt::format("Fail parse UserType, get unexpected value: {}", str));
}
UserType Parse(const userver::formats::json::Value& value,
               userver::formats::parse::To<UserType>)
{
    if (!value.IsString())
    {
        throw std::runtime_error(fmt::format(
            "Expected string type, but got: {}", utils::GetType(value)));
    }
    auto raw_value = value.As<std::string>();
    return Parse(std::string_view{raw_value},
                 userver::formats::parse::To<UserType>{});
}
}  // namespace timetable_vsu_backend::models
