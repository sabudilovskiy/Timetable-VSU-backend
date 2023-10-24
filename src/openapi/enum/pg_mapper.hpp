#pragma once
#include <openapi/enum/enumerator_func.hpp>
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>
#include <utils/constexpr_string.hpp>

namespace openapi
{
// should be in namespace userver::storages::postgres::io
template <typename T, utils::ConstexprString str>
requires HasIntrospector<T> struct PgMapper
    : userver::storages::postgres::io::EnumMappingBase<T>
{
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        str.data();
    static constexpr userver::utils::TrivialBiMap enumerators =
        create_enumerator_func<T>();
};

}  // namespace openapi
