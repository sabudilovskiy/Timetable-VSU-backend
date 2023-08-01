#pragma once

#include <optional>
#include <vector>

#include "property_base.hpp"
#include "userver/formats/json/value.hpp"

namespace timetable_vsu_backend::openapi
{
template <checks::IsReflective T, typename Traits = EmptyTraits>
struct ExtendedObjectProperty : public PropertyBase<T, Traits>
{
    userver::formats::json::Value additional_properties{};
    const userver::formats::json::Value& GetAdditionalProperties()
    {
        return additional_properties;
    }
};

}  // namespace timetable_vsu_backend::openapi
