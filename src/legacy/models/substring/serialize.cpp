#include "serialize.hpp"

#include <userver/formats/json/value_builder.hpp>
#include <userver/utils/datetime.hpp>

namespace legacy::models
{
// std::string Serialize(const SubString& value,
//                       userver::formats::serialize::To<std::string>)
// {
//     return value.GetUnderlying().substr(1, value.GetUnderlying().size() - 2);
// }
userver::formats::json::Value Serialize(
    const SubString& value,
    userver::formats::serialize::To<userver::formats::json::Value>)
{
    return userver::formats::json::ValueBuilder{value.GetUnderlying()}
        .ExtractValue();
}
}  // namespace legacy::models
