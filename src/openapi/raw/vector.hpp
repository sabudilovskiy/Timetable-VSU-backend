#pragma once
#include <openapi/raw/default.hpp>
#include <vector>

namespace timetable_vsu_backend::openapi::raw
{
template <IsDefault T>
class Raw<std::vector<T>>
{
    using Type = std::vector<T>;

   public:
    using result_mut = std::vector<T>&;
    using result_const = const std::vector<T>&;
    static result_mut Do(Type& t)
    {
        return t;
    }
    static result_const Do(const Type& t)
    {
        return t;
    }
};
template <IsNotDefault T>
class Raw<std::vector<T>>
{
    using Type = std::vector<T>;
    using RawMutT = typename Raw<T>::result_mut;
    using RawConstT = typename Raw<T>::result_const;

   public:
    using result_mut = std::vector<RawMutT>;
    using result_const = std::vector<RawConstT>;
    static result_mut Do(Type& t)
    {
        result_mut res;
        res.reserve(t.size());
        for (auto& elem : t)
        {
            res.emplace_back(Raw<T>::Do(elem));
        }
        return res;
    }
    static result_const Do(const Type& t)
    {
        result_const res;
        res.reserve(t.size());
        for (auto& elem : t)
        {
            res.emplace_back(Raw<T>::Do(elem));
        }
        return res;
    }
};
}  // namespace timetable_vsu_backend::openapi::raw
