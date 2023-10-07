#pragma once
#include <openapi/from_tuple/default.hpp>
#include <vector>
#include <type_traits>
#include "openapi/to_tuple/default.hpp"

namespace openapi::raw{
    template <IsDefaultToTuple T>
    class FromTuple<std::vector<T>>{
    public:
        using Dst = std::vector<T>;
        using Src = Dst;
        static Dst Do(const Src& src){
            return src;
        }
    };
    template <IsNotDefaultToTuple T>
    class FromTuple<std::vector<T>>{
        using Raw = to_tuple_t<T>;
    public:
        using Src = std::vector<Raw>;
        using Dst = std::vector<T>;
        static Dst Do(const Src& src){
            Dst result;
            result.reserve(src.size());
            for (auto& elem: src){
                result.emplace_back(FromTuple<T>::Do(elem));
            }
            return result;
        }
    };
}