#include "json_type.hpp"

#include <userver/formats/json.hpp>
#include <userver/formats/json/impl/types.hpp>

namespace timetable_vsu_backend::utils
{
std::string_view GetType(const userver::formats::json::Value& value)
{
    if (value.IsNull())
    {
        return "Null";
    }
    else if (value.IsArray())
    {
        return "Array";
    }
    else if (value.IsBool())
    {
        return "Bool";
    }
    else if (value.IsDouble())
    {
        return "Double";
    }
    else if (value.IsInt())
    {
        return "Int";
    }
    else if (value.IsInt64())
    {
        return "Int64";
    }
    else if (value.IsUInt64())
    {
        return "UInt64";
    }
    else if (value.IsObject())
    {
        return "Object";
    }
    else if (value.IsString())
    {
        return "String";
    }
    else
        return "Unknown";
}
}  // namespace timetable_vsu_backend::utils
