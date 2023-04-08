#pragma once
#include <boost/pfr/core.hpp>
#include <userver/formats/json.hpp>

#include "userver/formats/json/value.hpp"
#include "userver/server/http/http_request.hpp"
#include "utils/convert/base.hpp"

namespace timetable_vsu_backend::utils::convert::detail::parse {
template <typename T>
struct ConverterHttpRequest {
    static void Parse(T& t, const userver::server::http::HttpRequest& value) {
        auto tuple = GetTuple(t);
        static_assert(HasTypeOfBody<T>, "Type must have kTypeOfBody");
        auto body = GetBody<T::kTypeOfBody>(value);
        ParseTuple(value, body, tuple, IndexSequence{});
    }

   protected:
    //тип для обозначения пустого тела
    struct EmptyBody {};
    using ValueType = T;
    using TupleType =
        decltype(boost::pfr::structure_tie(std::declval<ValueType&>()));
    static constexpr std::size_t kSize = std::tuple_size<TupleType>::value;
    using IndexSequence = std::make_index_sequence<kSize>;
    static TupleType GetTuple(ValueType& v) {
        return boost::pfr::structure_tie(v);
    }

    //проверяем, что каждое поле кортежа является Property
    template <typename... Properties>
    static constexpr void check_properties(const std::tuple<Properties...>&) {
        static_assert((IsAnyProperty<std::remove_cvref_t<Properties>> && ...),
                      "Not all properties satisfy IsProperty concept");
    }
    //невозможно распарсить поле из тела, если оно пустое
    template <IsProperty Field>
    static void ParseField(const userver::server::http::HttpRequest&,
                           const EmptyBody&, Field&) {
        auto bad = []<bool flag = false>() {
            static_assert(flag,
                          "Found property from body, but body marked empty");
        };
    }
    //парсим поле из json тела
    template <IsProperty Field>
    static void ParseField(const userver::server::http::HttpRequest&,
                           const userver::formats::json::Value& body,
                           Field& field) {
        static constexpr std::string_view kName = Field::kName;
        field = body[kName].template As<Field>();
    }
    //парсим поле из query
    template <IsQueryProperty Field>
    static void ParseField(const userver::server::http::HttpRequest& value,
                           const userver::formats::json::Value&, Field& field) {
        static constexpr std::string_view kName = Field::kName;
        using FieldValue = typename Field::value_type;
        std::string temp{kName};
        auto& query_value = value.GetArg(temp);
        if constexpr (std::is_same_v<FieldValue, std::string>) {
            field = Field{query_value};
        } else {
            field =
                Parse(query_value, userver::formats::parse::To<FieldValue>{});
        }
    }
    //парсим поле из cookie
    template <IsCookieProperty Field>
    static void ParseField(const userver::server::http::HttpRequest& value,
                           const userver::formats::json::Value&, Field& field) {
        static constexpr std::string_view kName = Field::kName;
        using FieldValue = typename Field::value_type;
        std::string temp{kName};
        auto& cookie_value = value.GetCookie(temp);
        if constexpr (std::is_same_v<FieldValue, std::string>) {
            field = Field{cookie_value};
        } else {
            field =
                Parse(cookie_value, userver::formats::parse::To<FieldValue>{});
        }
    }
    //парсим поле из header
    template <IsHeaderProperty Field>
    static void ParseField(const userver::server::http::HttpRequest& value,
                           const userver::formats::json::Value&, Field& field) {
        static constexpr std::string_view kName = Field::kName;
        using FieldValue = typename Field::value_type;
        std::string temp{kName};
        auto& header_value = value.GetHeader(temp);
        if constexpr (std::is_same_v<FieldValue, std::string>) {
            field = Field{header_value};
        } else {
            field =
                Parse(header_value, userver::formats::parse::To<FieldValue>{});
        }
    }
    //Паттерн-матчинг относительно типа поля
    template <TypeOfBody type_of_body>
    static auto GetBody(const userver::server::http::HttpRequest& value) {
        if constexpr (type_of_body == TypeOfBody::Json) {
            return userver::formats::json::FromString(value.RequestBody());
        } else {
            return EmptyBody{};
        }
    }
    template <typename Tuple, typename Body, std::size_t... Indexes>
    static void ParseTuple(const userver::server::http::HttpRequest& value,
                           const Body& body, Tuple&& tuple,
                           std::index_sequence<Indexes...>) {
        check_properties(tuple);
        //парсим все поля
        (ParseField(value, body, std::get<Indexes>(tuple)), ...);
    }
};
}  // namespace timetable_vsu_backend::utils::convert::detail::parse