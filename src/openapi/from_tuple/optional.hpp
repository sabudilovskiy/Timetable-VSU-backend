#pragma once
#include <openapi/from_tuple/default.hpp>
#include <openapi/to_tuple/default.hpp>
#include <optional>
#include <type_traits>

namespace openapi::raw
{
template <IsDefaultToTuple T>
class FromTuple<std::optional<T>>
{
   public:
    using Dst = std::optional<T>;
    using Src = Dst;
    static Dst Do(const Src& src)
    {
        return src;
    }
};
template <IsNotDefaultToTuple T>
class FromTuple<std::optional<T>>
{
    using Raw = to_tuple_t<T>;

   public:
    using Src = std::optional<Raw>;
    using Dst = std::optional<T>;
    static Dst Do(const Src& src)
    {
        if (src.has_value())
        {
            return FromTuple<T>::Do(src.value());
        }
        else
            return std::nullopt;
    }
};
}  // namespace openapi::raw
