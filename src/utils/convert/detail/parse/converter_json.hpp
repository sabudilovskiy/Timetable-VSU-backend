#pragma once
#include <boost/pfr/core.hpp>
#include <userver/formats/json.hpp>

#include "utils/convert/base.hpp"

namespace timetable_vsu_backend::utils::convert::detail::parse
{
template <typename T>
struct ConverterJson
{
    static void Do(T& t, const userver::formats::json::Value& value)
    {
        auto tuple = GetTuple(t);
        ParseTuple(value, std::move(tuple), IndexSequence{});
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
    static TupleType GetTuple(ValueType& v)
    {
        return boost::pfr::structure_tie(v);
    }
    //для парса поля достаем соответствующее поле JSON по названию из Property
    template <typename Field>
    static void ParseField(const userver::formats::json::Value& value,
                           Field& field)
    {
        static constexpr std::string_view kName = Field::kName;
        using FieldValue = typename Field::value_type;
        if (value.IsNull())
        {
            throw std::runtime_error(fmt::format(
                "Unexpected null json get while parsing field: {}", kName));
        }
        else if (value.IsMissing())
        {
            throw std::runtime_error(fmt::format(
                "Unexpected missing json get while parsing field: {}", kName));
        }
        if (!value.HasMember(kName))
        {
            if constexpr (userver::meta::kIsOptional<FieldValue>)
            {
                field = std::nullopt;
            }
            else
            {
                throw std::runtime_error(
                    fmt::format("Missing field: {}", kName));
            }
        }
        field = value[kName].template As<Field>();
    }
    //проверяем, что каждое поле кортежа является Property
    template <typename... Properties>
    static constexpr void check_properties(const std::tuple<Properties...>&)
    {
        static_assert((IsProperty<std::remove_cvref_t<Properties>> && ...),
                      "Not all properties satisfy IsProperty concept");
    }
    template <std::size_t... Indexes>
    static void ParseTuple(const userver::formats::json::Value& value,
                           TupleType&& tuple, std::index_sequence<Indexes...>)
    {
        check_properties(tuple);
        //парсим каждое поле
        (ParseField(value, std::get<Indexes>(tuple)), ...);
    }
};
}  // namespace timetable_vsu_backend::utils::convert::detail::parse
