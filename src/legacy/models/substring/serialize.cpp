#include "serialize.hpp"

#include <userver/formats/json/value_builder.hpp>
#include <userver/utils/datetime.hpp>

namespace legacy::models
{
std::string Serialize(const SubString& value,
                      userver::formats::serialize::To<std::string>)
{
    return value.GetUnderlying().substr(1, value.GetUnderlying().size() - 2);
}
userver::formats::json::Value Serialize(
    const SubString& value,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    std::string str =
        Serialize(value, userver::formats::serialize::To<std::string>{});
    return userver::formats::json::ValueBuilder(str).ExtractValue();
}
}  // namespace legacy::models
