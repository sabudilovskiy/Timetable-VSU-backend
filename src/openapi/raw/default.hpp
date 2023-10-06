#pragma once

#include <type_traits>

namespace timetable_vsu_backend::openapi::raw
{
//Специализации этого типа не должны работать по-разному для const и mut
template <typename T>
class Raw
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
using raw_mut_t = typename Raw<T>::result_mut;

template <typename T>
using raw_const_t = typename Raw<T>::result_const;

template <typename T>
concept IsDefault = std::is_same_v<raw_mut_t<T>, T&>;

template <typename T>
concept IsNotDefault = !IsDefault<T>;
}  // namespace timetable_vsu_backend::openapi::raw
