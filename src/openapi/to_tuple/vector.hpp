#pragma once
#include <openapi/to_tuple/default.hpp>
#include <vector>

namespace openapi::raw
{
template <IsDefaultToTuple T>
class ToTuple<std::vector<T>>
{
    using Type = std::vector<T>;

   public:
    using result = Type;
    static result Do(Type& t)
    {
        return t;
    }
    static result Do(const Type& t)
    {
        return t;
    }
};
template <IsNotDefaultToTuple T>
class ToTuple<std::vector<T>>
{
    using Type = std::vector<T>;
    using Raw = to_tuple_t<T>;

   public:
    using result = std::vector<Raw>;
    static result Do(Type& t)
    {
        result res;
        res.reserve(t.size());
        for (auto& elem : t)
        {
            res.emplace_back(ToTuple<T>::Do(elem));
        }
        return res;
    }
    static result Do(const Type& t)
    {
        result res;
        res.reserve(t.size());
        for (auto& elem : t)
        {
            res.emplace_back(ToTuple<T>::Do(elem));
        }
        return res;
    }
};
}  // namespace openapi::raw
