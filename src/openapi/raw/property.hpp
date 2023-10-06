#pragma once

#include <openapi/base/property_base.hpp>
#include <openapi/raw/default.hpp>
namespace timetable_vsu_backend::openapi::raw
{
template <IsProperty U>
class Raw<U>
{
    using T = typename U::value_type;
    using Traits = typename U::traits;
    using Type = PropertyBase<T, Traits>;
    using RawMut = typename Raw<T>::result_mut;
    using RawConst = typename Raw<T>::result_const;

   public:
    using result_mut = RawMut;
    using result_const = RawConst;
    static result_mut Do(Type& t)
    {
        return Raw<T>::Do(t());
    }
    static result_const Do(const Type& t)
    {
        return Raw<T>::Do(t());
    }
};
}  // namespace timetable_vsu_backend::openapi::raw
