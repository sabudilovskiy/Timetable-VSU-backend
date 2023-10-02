#pragma once
#include <boost/pfr/core.hpp>
#include <userver/formats/json.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/server/http/http_response.hpp>
#include <utils/convert/base.hpp>
#include <utils/convert/http_response_base.hpp>

namespace timetable_vsu_backend::utils::convert::detail::serialize
{
template <typename T>
struct ConverterHttpResponse
{
    static void Do(const T& t, HttpResponse& response)
    {
        auto tuple = GetTuple(t);
        static_assert(HasTypeOfBody<T>, "Type must have kTypeOfBody");
        static_assert(HasStatusCode<T>, "Type must have kStatusCode");
        auto body = GetBody<T::kTypeOfBody>();
        SerializeTuple(response, body, tuple, IndexSequence{});
        SetStatus(response);
        TranslateBody(response, body);
    }

   protected:
    struct EmptyBody
    {
    };
    static void SetStatus(HttpResponse& response)
    {
        response().SetStatus(T::kStatusCode);
    }
    static void TranslateBody(HttpResponse& response, EmptyBody&)
    {
        response.body = "";
    }
    static void TranslateBody(HttpResponse& response,
                              userver::formats::json::ValueBuilder& body)
    {
        response.body = ToString(body.ExtractValue());
    }
    using ValueType = T;
    //кортеж константных ссылок на поля изначальной структуры
    using ConstTupleType =
        decltype(boost::pfr::structure_tie(std::declval<const ValueType&>()));
    //количество полей структуры
    static constexpr std::size_t size = std::tuple_size<ConstTupleType>::value;
    //последовательность индексов для обхода полей
    using IndexSequence = std::make_index_sequence<size>;
    //создаем кортеж ссылок на поля изначальной структуры
    static ConstTupleType GetTuple(const ValueType& v)
    {
        return boost::pfr::structure_tie(v);
    }

    //проверяем, что каждое поле кортежа является Property
    template <typename... Properties>
    static constexpr void check_properties(const std::tuple<Properties...>&)
    {
        static_assert((IsAnyProperty<std::remove_cvref_t<Properties>> && ...),
                      "Not all properties satisfy IsProperty concept");
    }
    //невозможно распарсить поле в тело, если оно пустое
    template <IsProperty Field>
    static void SerializeField(HttpResponse&, const EmptyBody&, const Field&)
    {
        auto bad = []<bool flag = false>()
        {
            static_assert(flag,
                          "Found property from body, but body marked empty");
        };
    }
    //сериализуем поле в json тело
    template <IsProperty Field>
    static void SerializeField(HttpResponse&,
                               userver::formats::json::ValueBuilder& body,
                               const Field& field)
    {
        static constexpr std::string_view kName = Field::kName;
        std::string temp{kName};
        body[temp] = field();
    }
    //сериализуем поле в query
    template <IsQueryProperty Field>
    static void SerializeField(HttpResponse&,
                               userver::formats::json::ValueBuilder&,
                               const Field&)
    {
        auto bad = []<bool flag = false>()
        {
            static_assert(
                flag,
                "A query property was found, which is invalid because "
                "response does not have a query");
        };
    }
    //сериализуем поле в cookie
    template <IsCookieProperty Field>
    static void SerializeField(HttpResponse& response,
                               userver::formats::json::ValueBuilder&,
                               const Field& field)
    {
        static constexpr std::string_view kName = Field::kName;
        std::string temp{kName};
        std::string field_value =
            Serialize(field(), userver::formats::serialize::To<std::string>{});
        //на самом деле там триллион параметров, для куки нужен отдельный
        //все-таки проперти и отдельная обработка
        userver::server::http::Cookie cookie{std::move(temp),
                                             std::move(field_value)};
        response().SetCookie(std::move(cookie));
    }
    //сериализуем поле в header
    template <IsHeaderProperty Field>
    static void SerializeField(HttpResponse& response,
                               userver::formats::json::ValueBuilder&,
                               const Field& field)
    {
        static constexpr std::string_view kName = Field::kName;
        std::string temp{kName};
        std::string field_value =
            Serialize(field(), userver::formats::serialize::To<std::string>{});
        response().SetHeader(std::move(temp), std::move(field_value));
    }
    //Паттерн-матчинг относительно типа поля
    template <TypeOfBody type_of_body>
    static auto GetBody()
    {
        if constexpr (type_of_body == TypeOfBody::Json)
        {
            //было бы неплохо поддерживать не только возврат как объекта, но
            //пока так
            return userver::formats::json::ValueBuilder(
                userver::formats::json::Type::kObject);
        }
        else
        {
            return EmptyBody{};
        }
    }
    template <typename Tuple, typename Body, std::size_t... Indexes>
    static void SerializeTuple(HttpResponse& response, Body& body,
                               Tuple&& tuple, std::index_sequence<Indexes...>)
    {
        check_properties(tuple);
        //сериализуем все поля
        (SerializeField(response, body, std::get<Indexes>(tuple)), ...);
    }
};
}  // namespace timetable_vsu_backend::utils::convert::detail::serialize
