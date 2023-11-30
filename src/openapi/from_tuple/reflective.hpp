#pragma once
#include <boost/pfr/core.hpp>
#include <openapi/base/properties/object.hpp>
#include <openapi/base/property_base.hpp>
#include <openapi/from_tuple/default.hpp>
#include <tuple>
#include <type_traits>
#include <utility>

namespace openapi::raw
{
template <typename T>
requires checks::is_reflective_v<T> class FromTuple<T>
{
   public:
    using Src = to_tuple_t<T>;
    using Dst = T;

   private:
    static constexpr auto Indexes =
        std::make_index_sequence<std::tuple_size_v<Src>>{};

    template <std::size_t Index>
    static auto HandleMember(const Src& src)
    {
        auto&& member = std::get<Index>(src);
        using DstMember = boost::pfr::tuple_element_t<Index, T>;
        return FromTuple<DstMember>::Do(member);
    }

    template <std::size_t... Index>
    static Dst Construct(const Src& src,
                         std::integer_sequence<std::size_t, Index...>)
    {
        return Dst{HandleMember<Index>(src)...};
    }

   public:
    static Dst Do(const Src& src)
    {
        auto indexes = Indexes;
        return Construct(src, indexes);
    }
};
}  // namespace openapi::raw
