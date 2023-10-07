#pragma once
#include <openapi/base/property_base.hpp>
#include <optional>
#include <type_traits>

namespace openapi
{
template <typename T>
concept IsOptionalProperty = requires
{
    typename T::value_type;
    typename T::traits;
    typename T::value_type::value_type;
    requires std::is_base_of_v<
        PropertyBase<std::optional<typename T::value_type::value_type>,
                     typename T::traits>,
        T>;
};
}  // namespace openapi
