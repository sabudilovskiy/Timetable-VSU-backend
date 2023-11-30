#pragma once
#include <openapi/to_tuple/default.hpp>
#include <type_traits>

namespace openapi::raw
{
template <typename T>
class FromTuple
{
   public:
    using Dest = T;
    using Src = to_tuple_t<Dest>;
    static Dest Do(const Src& src)
    {
        return src;
    }
};

template <typename T>
using dest_t = typename FromTuple<T>::Dest;

template <typename T>
using src_t = typename FromTuple<T>::Src;
}  // namespace openapi::raw
