#pragma once
#include <optional>
#include <userver/storages/postgres/exceptions.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/query.hpp>
#include <userver/storages/postgres/result_set.hpp>

#include "convert/base.hpp"
#include "userver/utils/meta.hpp"
#include "utils/convert/drop_properties_ref.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::utils
{
//Прямая конвертация используя встроенные методы pg_result не будет работать с
//рефлективными типами. Использует промежуточные кортежи ссылок для перегона
//данных.
template <typename To>
std::vector<To> ConvertPgResultToArray(
    const userver::storages::postgres::ResultSet& pg_result)
{
    if constexpr (convert::IsConvertAll<To>)
    {
        std::vector<To> result;
        result.reserve(pg_result.Size());
        for (auto& row : pg_result)
        {
            To to;
            auto tuple_to = convert::DropPropertiesToMutRefs(to);
            row.To(tuple_to, userver::storages::postgres::kRowTag);
            result.emplace_back(std::move(to));
        }
        return result;
    }
    else
        return pg_result.AsContainer<std::vector<To>>();
}
//Прямая конвертация используя встроенные методы pg_result не будет работать с
//рефлективными типами. Использует промежуточные кортежи ссылок для перегона
//данных.
//@throws userver::storages::postgres::NonSingleRowResultSet, если размер сета
//!= 1
template <typename To>
To ConvertPgResultToItem(
    const userver::storages::postgres::ResultSet& pg_result)
{
    if (pg_result.Size() != 1)
    {
        throw userver::storages::postgres::NonSingleRowResultSet(
            pg_result.Size());
    }
    if constexpr (convert::IsConvertAll<To>)
    {
        To to;
        auto tuple_to = convert::DropPropertiesToMutRefs(to);
        pg_result[0].To(tuple_to, userver::storages::postgres::kRowTag);
        return to;
    }
    else
        return pg_result.AsSingleRow<To>();
}

template <typename To>
std::optional<To> ConvertPgResultToOptionalItem(
    const userver::storages::postgres::ResultSet& pg_result)
{
    if (pg_result.Size() > 1)
    {
        throw userver::storages::postgres::NonSingleRowResultSet(
            pg_result.Size());
    }
    else if (pg_result.IsEmpty())
    {
        return std::nullopt;
    }
    if constexpr (convert::IsConvertAll<To>)
    {
        To to;
        auto tuple_to = convert::DropPropertiesToMutRefs(to);
        pg_result[0].To(tuple_to, userver::storages::postgres::kRowTag);
        return to;
    }
    else
        return pg_result.AsSingleRow<To>();
}

namespace details
{
//Небольшой хелпер, чтобы обобщить обработку рефлективных типов и нерефлективных
template <typename Arg>
decltype(auto) HelpForwardArg(const Arg& arg)
{
    //если это рефлективный тип, то превращаем в кортеж
    if constexpr (convert::DroppableToTupleRef<Arg> ||
                  convert::OptionalDroppableToTupleRef<Arg>)
    {
        return convert::DropPropertiesToConstRefs(arg);
    }
    //в противном случае ничего не делаем
    else
        return arg;
}
}  // namespace details

//обертка для повседневного использования магических структур
//так как было решено во всех контроллерах использовать shared transaction, то
//этого интерфейса достаточно
template <typename... Args>
userver::storages::postgres::ResultSet PgExecute(
    const timetable_vsu_backend::utils::SharedTransaction& transaction,
    const userver::storages::postgres::Query& query, const Args&... args)
{
    return transaction->transaction_.Execute(query,
                                             details::HelpForwardArg(args)...);
}
}  // namespace timetable_vsu_backend::utils
