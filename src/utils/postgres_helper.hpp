#pragma once
#include <optional>
#include <userver/storages/postgres/result_set.hpp>

#include "convert/base.hpp"
#include "userver/storages/postgres/exceptions.hpp"
#include "userver/storages/postgres/io/row_types.hpp"
#include "userver/storages/postgres/query.hpp"
#include "utils/convert/drop_properties_ref.hpp"
#include "utils/shared_transaction.hpp"

namespace timetable_vsu_backend::utils {
//Прямая конвертация используя встроенные методы pg_result не будет работать с
//рефлективными типами. Использует промежуточные кортежи ссылок для перегона
//данных.
template <convert::IsConvertAll To>
std::vector<To> ConvertPgResultToArray(
    const userver::storages::postgres::ResultSet& pg_result) {
    std::vector<To> result;
    result.reserve(pg_result.Size());
    for (auto& row : pg_result) {
        To to;
        auto tuple_to = convert::DropPropertiesToMutRefs(to);
        row.To(tuple_to, userver::storages::postgres::kRowTag);
        result.emplace_back(std::move(to));
    }
    return result;
}
//Прямая конвертация используя встроенные методы pg_result не будет работать с
//рефлективными типами. Использует промежуточные кортежи ссылок для перегона
//данных.
//@throws userver::storages::postgres::NonSingleRowResultSet, если размер сета
//!= 1
template <convert::IsConvertAll To>
To ConvertPgResultToItem(
    const userver::storages::postgres::ResultSet& pg_result) {
    if (pg_result.Size() != 1) {
        throw userver::storages::postgres::NonSingleRowResultSet(
            pg_result.Size());
    }
    To to;
    auto tuple_to = convert::DropPropertiesToMutRefs(to);
    pg_result[0].To(tuple_to, userver::storages::postgres::kRowTag);
    return to;
}

template <convert::IsConvertAll To>
std::optional<To> ConvertPgResultToOptionalItem(
    const userver::storages::postgres::ResultSet& pg_result) {
    if (pg_result.Size() > 1) {
        throw userver::storages::postgres::NonSingleRowResultSet(
            pg_result.Size());
    } else if (pg_result.IsEmpty()) {
        return std::nullopt;
    }
    To to;
    auto tuple_to = convert::DropPropertiesToMutRefs(to);
    pg_result[0].To(tuple_to, userver::storages::postgres::kRowTag);
    return to;
}
//обертка для повседневного использования магических структур
//так как было решено во всех контроллерах использовать shared transaction, то
//этого интерфейса достаточно
template <convert::IsConvertAll... Args>
userver::storages::postgres::ResultSet PgExecute(
    const vsu_timetable::utils::SharedTransaction& transaction,
    const userver::storages::postgres::Query& query, Args&&... args) {
    auto some_magic =
        [... tuple_args = convert::DropPropertiesToConstRefs(args)](
            const vsu_timetable::utils::SharedTransaction& transaction,
            const userver::storages::postgres::Query& query) mutable {
            return transaction->transaction_.Execute(query, tuple_args...);
        };
    return some_magic(transaction, query);
}
//обертка для повседневного использования магических структур
//так как было решено во всех контроллерах использовать shared transaction, то
//этого интерфейса достаточно
template <convert::IsConvertAll... Args>
userver::storages::postgres::ResultSet PgExecute(
    const vsu_timetable::utils::SharedTransaction& transaction,
    const userver::storages::postgres::Query& query,
    const std::optional<Args>&... args) {
    auto some_magic =
        [... tuple_args = convert::DropPropertiesToConstRefs(args)](
            const vsu_timetable::utils::SharedTransaction& transaction,
            const userver::storages::postgres::Query& query) mutable {
            return transaction->transaction_.Execute(query, tuple_args...);
        };
    return some_magic(transaction, query);
}
}  // namespace timetable_vsu_backend::utils
