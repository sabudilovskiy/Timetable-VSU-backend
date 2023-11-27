#pragma once

#include <openapi/as_tuple/default.hpp>
#include <openapi/base/property_base.hpp>
namespace openapi::raw
{
template <IsProperty U>
class AsTuple<U>
{
    using T = typename U::value_type;
    static constexpr auto& Traits = U::traits;
    using Type = PropertyBase<T, Traits>;
    using RawMut = typename AsTuple<T>::result_mut;
    using RawConst = typename AsTuple<T>::result_const;

   public:
    using result_mut = RawMut;
    using result_const = RawConst;
    static result_mut Do(Type& t)
    {
        return AsTuple<T>::Do(t());
    }
    static result_const Do(const Type& t)
    {
        return AsTuple<T>::Do(t());
    }
};
}  // namespace openapi::raw
