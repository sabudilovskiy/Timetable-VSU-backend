#pragma once

#include <openapi/base/property_base.hpp>
#include <openapi/base/reflective/checks.hpp>
#include <type_traits>
#include <userver/storages/postgres/io/buffer_io_base.hpp>
#include <userver/storages/postgres/io/io_fwd.hpp>
#include <userver/storages/postgres/io/nullable_traits.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/storages/postgres/io/type_traits.hpp>
#include <utils/is_complete_type.hpp>

namespace openapi
{
template <typename T>
concept IsPgProperty =
    IsProperty<T>&& userver::storages::postgres::io::traits::kIsMappedToPg<
        typename T::value_type>;

}  // namespace openapi

namespace userver::storages::postgres::io
{
namespace detail
{
template <typename T>
requires openapi::IsProperty<T> struct OpenapiPropertyFormatter
    : BufferFormatterBase<T>
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

template <typename T>
requires openapi::IsProperty<T> struct OpenapiPropertyParser
    : BufferParserBase<T>
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
template <typename T>
requires openapi::IsProperty<T>&&
    traits::kHasFormatter<typename T::value_type> struct BufferFormatter<T>
    : detail::OpenapiPropertyFormatter<T>
{
    using BaseType = detail::OpenapiPropertyFormatter<T>;
    using BaseType::BaseType;
};

/*
Parser specialization for openapi::Property
*/
template <typename T>
requires openapi::IsProperty<T>&&
    traits::kHasParser<typename T::value_type> struct BufferParser<T>
    : detail::OpenapiPropertyParser<T>
{
    using BaseType = detail::OpenapiPropertyParser<T>;
    using BaseType::BaseType;
};

template <typename T>
requires openapi::IsProperty<T>&&
    traits::kIsNullable<typename T::value_type> struct traits::IsNullable<T>
    : traits::IsNullable<typename T::value_type>
{
};

template <typename T>
requires openapi::IsProperty<T>&&
    traits::kIsNullable<typename T::value_type> struct traits::GetSetNull<T>
{
    using inner_get_set = traits::GetSetNull<typename T::value_type>;
    inline static bool IsNull(const T& v)
    {
        return inner_get_set::IsNull(v());
    }
    inline static void SetNull(T& v)
    {
        inner_get_set::SetNull(v());
    }
    inline static void SetDefault(T& v)
    {
        inner_get_set::SetDefault(v());
    }
};

template <typename T>
requires openapi::IsPgProperty<T> struct CppToPg<T>
    : CppToPg<typename T::value_type>
{
};

template <typename T>
requires openapi::IsPgProperty<T> struct traits::IsMappedToPg<T>
    : traits::IsMappedToPg<typename T::value_type>
{
};

template <typename T>
requires openapi::IsPgProperty<T> struct traits::IsSpecialMapping<T>
    : traits::IsMappedToPg<typename T::value_type>
{
};

}  // namespace userver::storages::postgres::io
