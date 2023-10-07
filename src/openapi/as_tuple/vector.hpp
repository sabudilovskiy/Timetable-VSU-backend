#pragma once
#include <openapi/as_tuple/default.hpp>
#include <vector>

namespace openapi::raw
{
template <IsDefaultAsTuple T>
class AsTuple<std::vector<T>>
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
template <IsNotDefaultAsTuple T>
class AsTuple<std::vector<T>>
{
    using Type = std::vector<T>;
    using RawMutT = typename AsTuple<T>::result_mut;
    using RawConstT = typename AsTuple<T>::result_const;

   public:
    using result_mut = std::vector<RawMutT>;
    using result_const = std::vector<RawConstT>;
    static result_mut Do(Type& t)
    {
        result_mut res;
        res.reserve(t.size());
        for (auto& elem : t)
        {
            res.emplace_back(AsTuple<T>::Do(elem));
        }
        return res;
    }
    static result_const Do(const Type& t)
    {
        result_const res;
        res.reserve(t.size());
        for (auto& elem : t)
        {
            res.emplace_back(AsTuple<T>::Do(elem));
        }
        return res;
    }
};
}  // namespace openapi::raw
