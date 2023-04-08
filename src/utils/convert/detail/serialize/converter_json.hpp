#pragma once
#include <boost/pfr/core.hpp>

#include "userver/formats/json/value_builder.hpp"
#include "utils/convert/base.hpp"

namespace timetable_vsu_backend::utils::convert::detail::serialize {
template <typename T>
struct ConverterJson {
    static void Serialize(const T& t,
                          userver::formats::json::ValueBuilder& value) {
        auto tuple = GetTuple(t);
        SerializeTuple(value, std::move(tuple), IndexSequence{});
    }

   protected:
    using ValueType = T;
    //кортеж константных ссылок на поля изначальной структуры
    using ConstTupleType =
        decltype(boost::pfr::structure_tie(std::declval<const ValueType&>()));
    //количество полей структуры
    static constexpr std::size_t size = std::tuple_size<ConstTupleType>::value;
    //последовательность индексов для обхода полей
    using IndexSequence = std::make_index_sequence<size>;
    //создаем кортеж ссылок на поля изначальной структуры
    static ConstTupleType GetTuple(const ValueType& v) {
        return boost::pfr::structure_tie(v);
    }
    template <typename Field>
    static void SerializeField(userver::formats::json::ValueBuilder& value,
                               const Field& field) {
        constexpr std::string_view kName = Field::kName;
        std::string temp{kName};
        value.EmplaceNocheck(temp, field);
    }
    //проверка, что все поля являются Property
    template <typename... Properties>
    static constexpr void check_properties(const std::tuple<Properties...>&) {
        static_assert((IsProperty<std::remove_cvref_t<Properties>> && ...),
                      "Not all properties satisfy IsProperty concept");
    }

    template <std::size_t... Indexes>
    static void SerializeTuple(userver::formats::json::ValueBuilder& value,
                               ConstTupleType&& tuple,
                               std::index_sequence<Indexes...>) {
        check_properties(tuple);
        //сериализуем все поля при помощи индексов
        (SerializeField(value, std::get<Indexes>(tuple)), ...);
    }
};
}  // namespace timetable_vsu_backend::utils::convert::detail::serialize