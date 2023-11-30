#pragma once

#include <type_traits>

namespace openapi::raw
{
//Специализации этого типа не должны работать по-разному для const и mut
template <typename T>
class ToTuple
{
    using Type = T;

   public:
    using result = T;
    static result Do(Type& t)
    {
        return t;
    }
    static result Do(const Type& t)
    {
        return t;
    }
};

template <typename T>
using to_tuple_t = typename ToTuple<T>::result;

template <typename T>
concept IsDefaultToTuple = std::is_same_v<to_tuple_t<T>, T>;

template <typename T>
concept IsNotDefaultToTuple = !IsDefaultToTuple<T>;
}  // namespace openapi::raw
