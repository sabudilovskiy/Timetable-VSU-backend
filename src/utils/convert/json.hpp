#pragma once
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <boost/pfr.hpp>
#include <string_view>
#include <type_traits>
#include <userver/formats/json.hpp>
#include <userver/utest/utest.hpp>
#include <variant>
#include "base.hpp"
#include "userver/formats/json/value.hpp"
#include "userver/formats/json/value_builder.hpp"
#include "userver/logging/log.hpp"

namespace timetable_vsu_backend::utils::convert {
template <typename T>
struct ConverterJson {
  using ValueType = T;
  using TupleType =
      decltype(boost::pfr::structure_tie(std::declval<ValueType&>()));
  using ConstTupleType =
      decltype(boost::pfr::structure_tie(std::declval<const ValueType&>()));
  static constexpr std::size_t size = std::tuple_size<TupleType>::value;

  using IndexSequence = std::make_index_sequence<size>;
  static void Read(T& t, const userver::formats::json::Value& value) {
    auto tuple = GetTuple(t);
    ReadTuple(value, std::move(tuple), IndexSequence{});
  }
  static void Write(const T& t, userver::formats::json::ValueBuilder& value) {
    auto tuple = GetTuple(t);
    WriteTuple(value, std::move(tuple), IndexSequence{});
  }
  static TupleType GetTuple(ValueType& v) {
    return boost::pfr::structure_tie(v);
  }
  static ConstTupleType GetTuple(const ValueType& v) {
    return boost::pfr::structure_tie(v);
  }
  template <typename Field>
  static void ReadField(const userver::formats::json::Value& value,
                        Field& field) {
    static constexpr std::string_view kName = Field::kName;
    field = value[kName].template As<Field>();
  }
  template <typename Field>
  static void WriteField(userver::formats::json::ValueBuilder& value,
                         const Field& field) {
    constexpr std::string_view kName = Field::kName;
    std::string temp{kName};
    value.EmplaceNocheck(temp, field);
  }
  template <typename... Properties>
  static constexpr void check_properties(
      const std::tuple<Properties...>& props) {
    static_assert((IsProperty<std::remove_cvref_t<Properties>> && ...),
                  "Not all properties satisfy IsProperty concept");
  }
  template <std::size_t... Indexes>
  static void ReadTuple(const userver::formats::json::Value& value,
                        TupleType&& tuple, std::index_sequence<Indexes...>) {
    check_properties(tuple);
    (ReadField(value, std::get<Indexes>(tuple)), ...);
  }
  template <std::size_t... Indexes>
  static void WriteTuple(userver::formats::json::ValueBuilder& value,
                         ConstTupleType&& tuple,
                         std::index_sequence<Indexes...>) {
    check_properties(tuple);
    (WriteField(value, std::get<Indexes>(tuple)), ...);
  }
};
}  // namespace timetable_vsu_backend::utils::convert

namespace userver::formats::parse {
using timetable_vsu_backend::utils::convert::IsConvertAll;
using timetable_vsu_backend::utils::convert::IsProperty;

template <IsProperty T>
T Parse(const json::Value& value, To<T>) {
  return T{value.As<typename T::value_type>()};
}

template <IsConvertAll T>
T Parse(const json::Value& value, To<T>) {
  T t;
  timetable_vsu_backend::utils::convert::ConverterJson<T>::Read(t, value);
  return t;
}

}  // namespace userver::formats::parse

namespace userver::formats::serialize {
using timetable_vsu_backend::utils::convert::IsConvertAll;
using timetable_vsu_backend::utils::convert::IsProperty;

template <IsProperty T>
json::Value Serialize(const T& t, To<json::Value>) {
  return json::ValueBuilder(t.value).ExtractValue();
}

template <IsConvertAll T>
json::Value Serialize(const T& t, To<json::Value>) {
  json::ValueBuilder json;
  timetable_vsu_backend::utils::convert::ConverterJson<T>::Write(t, json);
  return json.ExtractValue();
}
}  // namespace userver::formats::serialize