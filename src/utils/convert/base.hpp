#pragma once
#include <concepts>
#include <type_traits>
#include <utility>
// #include "utlis/convert/constexpr_string.hpp"
#include <utils/constexpr_string.hpp>
#include <utils/meta.hpp>

namespace utils::convert
{
//В данный момент поддерживаются только конвертация всех полей
enum struct PolicyFields
{
    ConvertAll
};

//тип тела в запросе
enum struct TypeOfBody
{
    Empty,  // Empty body = body игнорируеттся
    Json
};

//указание откуда следует парсить в http запросе
enum struct RequestParse
{
    Unspecified,  //данное поле в запросах будет парсится из body
    Query,
    Header,
    Cookie
};

template <typename T, ConstexprString name,
          RequestParse request_parse = RequestParse::Unspecified>
struct BaseProperty
{
    using value_type = T;
    constexpr auto static kName = name;
    constexpr auto static kRequestParse = request_parse;

    template <class Arg>
    value_type& operator=(Arg&& arg)
    {
        value = std::forward<Arg>(arg);
        return value;
    }
    value_type& operator()()
    {
        return value;
    }
    const value_type& operator()() const
    {
        return value;
    }
    value_type value;
};

template <typename T, ConstexprString name>
using Property = BaseProperty<T, name, RequestParse::Unspecified>;

template <typename T, ConstexprString name>
using QueryProperty = BaseProperty<T, name, RequestParse::Query>;

template <typename T, ConstexprString name>
using HeaderProperty = BaseProperty<T, name, RequestParse::Header>;

template <typename T, ConstexprString name>
using CookieProperty = BaseProperty<T, name, RequestParse::Cookie>;

template <typename T>
concept IsProperty = std::is_class_v<T>&&
    std::is_same_v<Property<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsQueryProperty = std::is_class_v<T>&&
    std::is_same_v<QueryProperty<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsHeaderProperty = std::is_class_v<T>&&
    std::is_same_v<HeaderProperty<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsCookieProperty = std::is_class_v<T>&&
    std::is_same_v<CookieProperty<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsAnyProperty = std::is_class_v<T>&& std::is_same_v<
    BaseProperty<typename T::value_type, T::kName, T::kRequestParse>, T>;

template <typename T>
concept HasTypeOfBody = requires
{
    {
        T::kTypeOfBody
    }
    ->std::convertible_to<TypeOfBody>;
    requires IsConstexpr<T::kTypeOfBody>;
};

template <typename T>
concept IsConvertAll = requires
{
    requires T::kPolicyFields == PolicyFields::ConvertAll;
};
}  // namespace utils::convert
