#include <fmt/core.h>

#include <boost/pfr/core.hpp>
#include <optional>
#include <stdexcept>
#include <tuple>
#include <userver/formats/json.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/http/http_request.hpp>
#include <userver/utils/meta.hpp>
#include <utility>

#include "../../base.hpp"
namespace timetable_vsu_backend::utils::convert::detail::drop_properties {
template <typename T>
struct DropperToRef final {
    static auto Do(T& t) {
        auto tuple = GetTuple(t);
        return HandleTuple(tuple, IndexSequence{});
    }

   protected:
    using ValueType = T;
    //кортеж ссылок на изначальную структуру
    using TupleType =
        decltype(boost::pfr::structure_tie(std::declval<ValueType&>()));
    //количество полей
    static constexpr std::size_t size = std::tuple_size<TupleType>::value;
    //последовательность индексов для обхода полей
    using IndexSequence = std::make_index_sequence<size>;
    //создаем кортеж ссылок на изначальную структуру
    static TupleType GetTuple(ValueType& v) {
        return boost::pfr::structure_tie(v);
    }
    //если это propery, то через () получаем ссылку на изначальный объект под и
    //вызываем от него дроп
    template <IsAnyProperty Member>
    static decltype(auto) HandleMember(Member& member) {
        using MemberType = typename Member::value_type;
        //если под типом скрывается структура с Property, то юзаем дроппер для
        //него
        if constexpr (IsConvertAll<MemberType>) {
            return DropperToRef<MemberType>::Do(member());
        }
        //в противном случае просто возвращаем ссылку на оригинальный тип
        else {
            return member();
        }
    }
    template <typename Tuple, std::size_t Index>
    static decltype(auto) HelpHandleMember(Tuple& tuple) {
        return HandleMember(std::get<Index>(tuple));
    }
    template <typename... Type>
    static auto ConstructResult(Type&&... values){
        return std::tuple<decltype(values)...>(std::forward<Type>(values)...);
    }
    template <typename Tuple, std::size_t... Indexes>
    static decltype(auto) HandleTuple(Tuple& tuple, std::index_sequence<Indexes...>) {
        return ConstructResult(HelpHandleMember<Tuple, Indexes>(tuple)...);
    }
};
}  // namespace timetable_vsu_backend::utils::convert::detail::drop_properties