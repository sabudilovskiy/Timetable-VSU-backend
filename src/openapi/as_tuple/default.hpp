#pragma once

#include <type_traits>

namespace openapi::raw
{
//Специализации этого типа не должны работать по-разному для const и mut
template <typename T>
class AsTuple
{
    using Type = T;

   public:
    using result_mut = T&;
    using result_const = const T&;
    static result_mut Do(Type& t)
    {
        return t;
    }
    static result_const Do(const Type& t)
    {
        return t;
    }
};

template <typename T>
using as_tuple_mut_t = typename AsTuple<T>::result_mut;

template <typename T>
using as_tuple_const_t = typename AsTuple<T>::result_const;

template <typename T>
concept IsDefaultAsTuple = std::is_same_v<as_tuple_mut_t<T>, T&>;

template <typename T>
concept IsNotDefaultAsTuple = !IsDefaultAsTuple<T>;
}  // namespace openapi::raw
