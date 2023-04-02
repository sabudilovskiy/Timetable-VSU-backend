#pragma once
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <boost/pfr.hpp>
#include <string>
#include <type_traits>
#include <userver/formats/json.hpp>
#include <userver/server/http/http_request.hpp>
#include <variant>
#include "base.hpp"
#include "userver/formats/json/value.hpp"
#include "userver/logging/log.hpp"

namespace timetable_vsu_backend::utils::convert {

template <typename T>
struct ConverterHttpRequest {
  struct EmptyBody {};
  using ValueType = T;
  using TupleType =
      decltype(boost::pfr::structure_tie(std::declval<ValueType&>()));
  static constexpr std::size_t size = std::tuple_size<TupleType>::value;

  using IndexSequence = std::make_index_sequence<size>;
  static void Read(T& t, const userver::server::http::HttpRequest& value) {
    auto tuple = GetTuple(t);
    static_assert(HasTypeOfBody<T>, "Type must have kTypeOfBody");
    auto body = GetBody<T::kTypeOfBody>();
    ReadTuple(value, body, tuple, IndexSequence{});
  }
  static TupleType GetTuple(ValueType& v) {
    return boost::pfr::structure_tie(v);
  }
  template <typename... Properties>
  static constexpr void check_properties(const std::tuple<Properties...>&) {
    static_assert((IsAnyProperty<Properties> && ...),
                  "Not all properties satisfy IsProperty concept");
  }
  template <typename Body, typename Field>
  static void ReadField(const userver::server::http::HttpRequest& value,
                        const Body& body, Field& field) {
    static constexpr std::string_view kName = Field::kName;
    using FieldValue = typename Field::value_type;
    if constexpr (IsProperty<Field> and !std::is_same_v<Body, EmptyBody>) {
      field = body[kName].template As<Field>();
    } else if constexpr (IsProperty<Field> and
                         std::is_same_v<Body, EmptyBody>) {
      static_assert(IsProperty<Field> and !std::is_same_v<Body, EmptyBody>,
                    "Found property from body, but body marked empty");
    } else if constexpr (IsQueryProperty<Field>) {
      std::string temp{kName};
      auto& query_value = value.GetArg(temp);
      if constexpr (std::is_same_v<FieldValue, std::string>) {
        field = Field{query_value};
      } else {
        field = Parse(query_value, userver::formats::parse::To<FieldValue>{});
      }
    } else if constexpr (IsHeaderProperty<Field>) {
      std::string temp{kName};
      auto& header_value = value.GetHeader(temp);
      if constexpr (std::is_same_v<FieldValue, std::string>) {
        field = Field{header_value};
      } else {
        field = Parse(header_value, userver::formats::parse::To<FieldValue>{});
      }
    }
  }
  template <TypeOfBody type_of_body>
  static auto GetBody(const userver::server::http::HttpRequest& value) {
    if constexpr (type_of_body == TypeOfBody::Json) {
      return userver::formats::json::FromString(value.RequestBody());
    } else {
      return EmptyBody{};
    }
  }
  template <typename Tuple, typename Body, std::size_t... Indexes>
  static void ReadTuple(const userver::server::http::HttpRequest& value,
                        Body&& body, Tuple&& tuple,
                        std::index_sequence<Indexes...>) {
    check_properties(tuple);
    (ReadField(value, body, std::get<Indexes>(tuple)), ...);
  }
};
}  // namespace timetable_vsu_backend::utils::convert

namespace userver::formats::parse {
using timetable_vsu_backend::utils::convert::IsConvertAll;
using timetable_vsu_backend::utils::convert::IsProperty;

template <IsProperty T>
T Parse(const formats::json::Value& value, formats::parse::To<T>) {
  return T{value.As<typename T::value_type>()};
}

template <IsConvertAll T>
T Parse(const formats::json::Value& value, formats::parse::To<T>) {
  T t;
  timetable_vsu_backend::utils::convert::ConverterHttpRequest<T>::Read(t,
                                                                       value);
  return t;
}
}  // namespace userver::formats::parse