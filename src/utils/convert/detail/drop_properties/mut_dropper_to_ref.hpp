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
#include "utils/convert/additional_properties.hpp"
#include "utils/type_holder.hpp"
namespace timetable_vsu_backend::utils::convert::detail::drop_properties {

template <typename T>
struct MutDropperToRef final {
    static auto Do(T& t) {
        auto tuple = GetTuple(t);
        return HandleTuple(tuple, IndexSequence{});
    }
    static auto ResultType() {
        return type_holder<decltype(MutDropperToRef::Do(std::declval<T&>()))>{};
    }

    //    protected:
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
    //если это usual propery, то через () получаем ссылку на изначальный объект
    //под
    template <IsUsualProperty Member>
    static decltype(auto) HandleMember(Member& member) {
        return member();
    }

    template <IsOptionalProperty Member>
    static decltype(auto) HandleMember(Member& member) {
        using NestedType = optional_property_t<Member>;
        //если вложенный тип структурный, то нужна дополнительная магия
        if constexpr (IsConvertAll<NestedType>) {
            //подсматривает результирующий тип
            using ResultTypeHelper =
                decltype(MutDropperToRef<NestedType>::ResultType());
            using ResultType = typename ResultTypeHelper::value_type;
            std::optional<ResultType> result = std::nullopt;
            if (member().has_value()) {
                result = MutDropperToRef<NestedType>::Do(member().value());
            }
            return result;
        } else {
            return member();
        }
    }

    template <IsArrayProperty Member>
    static decltype(auto) HandleMember(Member& member) {
        using NestedType = array_property_t<Member>;
        auto& value = member();
        //если вложенный тип структурный, то нужна дополнительная магия
        if constexpr (IsConvertAll<NestedType>) {
            //подсматривает результирующий тип
            using ResultTypeHelper =
                decltype(MutDropperToRef<NestedType>::ResultType());
            using ResultType = typename ResultTypeHelper::value_type;
            std::vector<ResultType> result;
            result.reserve(value.size());
            for (auto& elem : value) {
                result.emplace_back(MutDropperToRef<NestedType>::Do(elem));
            }
            return result;
        } else {
            return member();
        }
    }

    template <IsOptionalArrayProperty Member>
    static decltype(auto) HandleMember(Member& member) {
        using NestedType = optional_array_property_t<Member>;
        auto& value = member();
        //если вложенный тип структурный, то нужна дополнительная магия
        if constexpr (IsConvertAll<NestedType>) {
            //подсматривает результирующий тип
            using ResultTypeHelper =
                decltype(MutDropperToRef<NestedType>::ResultType());
            using ResultType = typename ResultTypeHelper::value_type;
            std::optional<std::vector<ResultType>> result = std::nullopt;
            if (value.has_value()) {
                result = std::vector<ResultType>{};
                result->reserve(value->size());
                for (auto& elem : *value) {
                    result.emplace_back(MutDropperToRef<NestedType>::Do(elem));
                }
            }
            return result;
        } else {
            return member();
        }
    }

    //если это структурное свойство, то раскладываем его
    template <IsStructuralProperty Member>
    static decltype(auto) HandleMember(Member& member) {
        using RawType = typename Member::value_type;
        return MutDropperToRef<RawType>::Do(member());
    }

    template <typename Tuple, std::size_t Index>
    static decltype(auto) HelpHandleMember(Tuple& tuple) {
        return HandleMember(std::get<Index>(tuple));
    }
    template <typename... Type>
    static auto ConstructResult(Type&&... values) {
        return std::tuple<Type...>(std::forward<Type>(values)...);
    }
    template <typename Tuple, std::size_t... Indexes>
    static decltype(auto) HandleTuple(Tuple& tuple,
                                      std::index_sequence<Indexes...>) {
        return ConstructResult(HelpHandleMember<Tuple, Indexes>(tuple)...);
    }
};
}  // namespace timetable_vsu_backend::utils::convert::detail::drop_properties