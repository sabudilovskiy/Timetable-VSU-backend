#pragma once

#include <openapi/base/property_base.hpp>
#include <openapi/to_tuple/default.hpp>
namespace openapi::raw
{
template <IsProperty U>
class ToTuple<U>
{
    using T = typename U::value_type;
    static constexpr auto& Traits = U::traits;
    using Type = PropertyBase<T, Traits>;
    using Raw = to_tuple_t<T>;

   public:
    using result = Raw;
    static result Do(Type& t)
    {
        return ToTuple<T>::Do(t());
    }
    static result Do(const Type& t)
    {
        return ToTuple<T>::Do(t());
    }
};
}  // namespace openapi::raw
