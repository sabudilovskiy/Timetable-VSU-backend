#pragma once

#include <openapi/base/property_base.hpp>
#include <openapi/base/reflective_checks.hpp>
#include <type_traits>
#include <userver/storages/postgres/io/buffer_io_base.hpp>
#include <userver/storages/postgres/io/io_fwd.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>
#include <utils/is_complete_type.hpp>

namespace openapi
{
template <typename T>
concept IsPgUserProperty = IsProperty<T>&& utils::is_complete_type<
    userver::storages::postgres::io::CppToUserPg<typename T::value_type>>;

template <typename T>
concept IsPgSystemProperty = IsProperty<T>&& utils::is_complete_type<
    userver::storages::postgres::io::CppToSystemPg<typename T::value_type>>;
}  // namespace openapi

namespace userver::storages::postgres::io
{
namespace detail
{
template <openapi::IsProperty T>
struct OpenapiPropertyFormatter : BufferFormatterBase<T>
{
    using Inner = typename T::value_type;
    using BaseType = BufferFormatterBase<T>;
    using ValueFormatter = typename traits::IO<Inner>::FormatterType;

    using BaseType::BaseType;

    template <typename Buffer>
    void operator()(const UserTypes& types, Buffer& buffer) const
    {
        ValueFormatter{this->value()}(types, buffer);
    }
};

template <openapi::IsProperty T>
struct OpenapiPropertyParser : BufferParserBase<T>
{
    using BaseType = BufferParserBase<T>;
    using Inner = typename T::value_type;
    using ValueParser = typename traits::IO<Inner>::ParserType;

    using BaseType::BaseType;

    void operator()(const FieldBuffer& buffer)
    {
        Inner val;
        ValueParser{val}(buffer);
        this->value() = std::move(val);
    }
};
}  // namespace detail

/*
Formatter specialization for openapi::Property
*/
template <openapi::IsProperty T>
struct BufferFormatter<
    T, std::enable_if_t<traits::kHasFormatter<typename T::value_type>>>
    : detail::OpenapiPropertyFormatter<T>
{
    using BaseType = detail::OpenapiPropertyFormatter<T>;
    using BaseType::BaseType;
};

/*
Parser specialization for openapi::Property
*/
template <openapi::IsProperty T>
struct BufferParser<
    T, std::enable_if_t<traits::kHasParser<typename T::value_type>>>
    : detail::OpenapiPropertyParser<T>
{
    using BaseType = detail::OpenapiPropertyParser<T>;
    using BaseType::BaseType;
};

template <typename T>
requires openapi::IsPgUserProperty<T> struct CppToUserPg<T>
{
   private:
    using Inner = typename T::value_type;

   public:
    static constexpr DBTypeName postgres_name =
        CppToUserPg<Inner>::postgres_name;
};

template <typename T>
requires openapi::IsPgSystemProperty<T> struct CppToSystemPg<T>
{
   private:
    using Inner = typename T::value_type;

   public:
    static constexpr auto value = CppToSystemPg<Inner>::value;
};

}  // namespace userver::storages::postgres::io
