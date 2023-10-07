#pragma once

#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <openapi/base/object_property.hpp>
#include <openapi/to_tuple/default.hpp>
#include <type_traits>
#include <utility>

namespace openapi::raw
{
template <checks::IsReflective T>
class ToTuple<T>
{
   private:
    using Type = T;
    static constexpr auto DefaultIndexes =
        std::make_index_sequence<boost::pfr::tuple_size_v<T>>{};
    template <typename Member>
    static decltype(auto) HandleMember(Member&& member)
    {
        using RawType = std::remove_cvref_t<Member>;
        return ToTuple<RawType>::Do(member);
    }

    template <std::size_t Index, typename Tuple>
    static decltype(auto) HelpHandleMember(Tuple&& tuple)
    {
        return HandleMember(boost::pfr::get<Index>(tuple));
    }

    template <typename... Element>
    static auto ConstructResult(Element&&... values)
    {
        return std::tuple<Element...>(std::forward<Element>(values)...);
    }
    template <typename Tuple, size_t... Indexes>
    static auto DoImpl(Tuple&& t, std::integer_sequence<size_t, Indexes...>)
    {
        return ConstructResult(HelpHandleMember<Indexes>(t)...);
    }

   public:
    static auto Do(Type& t)
    {
        auto indexes = DefaultIndexes;
        return DoImpl(t, indexes);
    }
    static auto Do(const Type& t)
    {
        auto indexes = DefaultIndexes;
        return DoImpl(t, indexes);
    }
    using result = decltype(Do(std::declval<Type&>()));
};
}  // namespace openapi::raw