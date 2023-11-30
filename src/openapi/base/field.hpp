#pragma once

#include <openapi/base/named_traits.hpp>
#include <openapi/base/property_base.hpp>
#include <utils/constexpr_string.hpp>
namespace openapi
{
namespace details
{
template <auto old_traits>
consteval auto trait_add_name(const utils::FixedString& name)
{
    static_assert(old_traits.name.empty(), "Don't use FIELD with Name<>");
    auto traits = old_traits;
    traits.name = name;
    return traits;
}
}  // namespace details
template <typename T, utils::FixedString name>
struct add_name
{
    using type = types::Property<T, NamedTraits{.name = name}>;
};
template <template <typename, auto> typename T, typename value_type,
          auto traits, utils::FixedString name>
requires IsProperty<T<value_type, traits>> struct add_name<
    T<value_type, traits>, name>
{
    using type = T<value_type, details::trait_add_name<traits>(name)>;
};

template <typename T, utils::FixedString name>
using add_name_t = typename add_name<T, name>::type;

}  // namespace openapi

#define FIELD(name, ...) ::openapi::add_name_t<__VA_ARGS__, #name> name
