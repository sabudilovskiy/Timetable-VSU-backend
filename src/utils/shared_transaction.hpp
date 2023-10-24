#pragma once
#include <boost/uuid/uuid.hpp>
#include <exception>
#include <string_view>
#include <type_traits>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/transaction.hpp>
#include <userver/utils/make_intrusive_ptr.hpp>

namespace utils
{
namespace details
{
template <typename T>
consteval bool IsRowType()
{
    auto value =
        userver::storages::postgres::io::traits::kRowCategory<T> !=
        userver::storages::postgres::io::traits::RowCategoryType::kNonRow;
    return value;
}
template <typename T>
T AsSingleRow(const userver::storages::postgres::ResultSet& pg_res)
{
    if constexpr (IsRowType<T>())
    {
        return pg_res.AsSingleRow<T>(userver::storages::postgres::kRowTag);
    }
    else
    {
        return pg_res.AsSingleRow<T>();
    }
}

template <typename Result>
Result AsContainer(const userver::storages::postgres::ResultSet& pg_res)
{
    if constexpr (IsRowType<typename Result::value_type>())
    {
        return pg_res.AsContainer<Result>(userver::storages::postgres::kRowTag);
    }
    else
    {
        return pg_res.AsContainer<Result>();
    }
}
}  // namespace details

// thread unsafe
// count owners
struct SafeTranscaction
{
    enum class ActionOnDeath
    {
        kCommit,
        kRollback,
        kNone
    };
    userver::storages::postgres::Transaction transaction_;
    template <typename... Args>
    userver::storages::postgres::ResultSet Execute(
        const userver::storages::postgres::Query& query, const Args&... args)
    {
        return transaction_.Execute(
            userver::storages::postgres::OptionalCommandControl{}, query,
            args...);
    }

    template <typename Result, typename... Args>
    Result Execute_R(const userver::storages::postgres::Query& query,
                     const Args&... args)
    {
        using namespace details;
        userver::storages::postgres::ResultSet pg_res = Execute(query, args...);
        if constexpr (userver::meta::kIsOptional<Result>)
        {
            if (pg_res.IsEmpty())
            {
                return std::nullopt;
            }
            return AsSingleRow<typename Result::value_type>(pg_res);
        }
        else if constexpr (userver::meta::kIsRange<Result> &&
                           !std::is_same_v<Result, boost::uuids::uuid>)
        {
            return AsContainer<Result>(pg_res);
        }
        else
        {
            return AsSingleRow<Result>(pg_res);
        }
    }
    SafeTranscaction(const userver::storages::postgres::ClusterPtr& ptr,
                     const std::string& name, bool auto_commit)
        : transaction_(ptr->Begin(
              name, userver::storages::postgres::ClusterHostType::kMaster, {}))
    {
        if (auto_commit)
        {
            action_on_death = ActionOnDeath::kCommit;
        }
        else
        {
            action_on_death = ActionOnDeath::kNone;
        }
    }

    SafeTranscaction(userver::storages::postgres::Transaction transction,
                     ActionOnDeath action_on_death)
        : transaction_(std::move(transction)), action_on_death(action_on_death)
    {
    }

    void Commit()
    {
        action_on_death = ActionOnDeath::kNone;
        transaction_.Commit();
    }

    void RollBack()
    {
        action_on_death = ActionOnDeath::kNone;
        transaction_.Commit();
    }

    friend void intrusive_ptr_add_ref(SafeTranscaction* transaction)
    {
        transaction->counter++;
    }

    friend void intrusive_ptr_release(SafeTranscaction* transaction)
    {
        transaction->counter--;
        if (transaction->counter == 0)
            delete transaction;
    }
    ~SafeTranscaction()
    {
        try
        {
            switch (action_on_death)
            {
                case ActionOnDeath::kCommit:
                    transaction_.Commit();
                    return;
                case ActionOnDeath::kRollback:
                    transaction_.Rollback();
                    return;
                case ActionOnDeath::kNone:
                    return;
            }
        }
        catch (std::exception& exc)
        {
            LOG_ERROR() << "Error while do action in SafeTransaction: "
                        << exc.what();
        }
    }

   private:
    ActionOnDeath action_on_death;
    size_t counter = 0;
};

/*
Интрузивный указатель используется для того, чтобы упростить использование
совместных транзакций.

Данный класс не является threadsafe, но является safe
относительно совместного использования между разными функциями.

Стандартное
применение предполагает получение интрузивного птр в каждом методе контроллера,
заполнение его при помощи FillSharedTransaction, чтобы гарантировать наличие
какое-либо транзакции.

По умолчанию выполняется коммит в деструкторе, чтобы
избежать этого поведения нужно задать противоположное. Благодаря этому явный
коммит не нужен.
*/
using SharedTransaction = boost::intrusive_ptr<SafeTranscaction>;

inline auto MakeSharedTransaction(
    const userver::storages::postgres::ClusterPtr& ptr,
    const std::string& name = "", bool auto_commit = true)
{
    return userver::utils::make_intrusive_ptr<SafeTranscaction>(ptr, name,
                                                                auto_commit);
}

inline void FillSharedTransaction(
    SharedTransaction& transaction,
    const userver::storages::postgres::ClusterPtr& ptr,
    const std::string& name = "", bool auto_commit = true)
{
    if (!transaction)
    {
        transaction = ::utils::MakeSharedTransaction(ptr, name, auto_commit);
    }
}

inline auto MakeSharedTransaction(
    const userver::storages::postgres::ClusterPtr& ptr,
    SafeTranscaction::ActionOnDeath action_on_death)
{
    return userver::utils::make_intrusive_ptr<SafeTranscaction>(
        ptr->Begin("", userver::storages::postgres::ClusterHostType::kMaster,
                   {}),
        action_on_death);
}

inline void FillSharedTransaction(
    SharedTransaction& transaction,
    const userver::storages::postgres::ClusterPtr& ptr,
    SafeTranscaction::ActionOnDeath action_on_death)
{
    if (!transaction)
    {
        transaction = ::utils::MakeSharedTransaction(ptr, action_on_death);
    }
}
}  // namespace utils
