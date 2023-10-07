#pragma once
#include <string_view>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/cluster_types.hpp>
#include <userver/storages/postgres/transaction.hpp>
#include <userver/utils/make_intrusive_ptr.hpp>

namespace utils
{
// thread unsafe
// count owners
struct SafeTranscaction
{
    userver::storages::postgres::Transaction transaction_;
    SafeTranscaction(const userver::storages::postgres::ClusterPtr& ptr,
                     const std::string& name, bool auto_commit)
        : transaction_(ptr->Begin(
              name, userver::storages::postgres::ClusterHostType::kMaster, {})),
          auto_commit_(auto_commit)
    {
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
        if (auto_commit_)
        {
            transaction_.Commit();
        }
    }

   private:
    bool auto_commit_;
    size_t counter = 0;
};

/*
Интрузивный указатель используется для того, чтобы упростить использование
совместных транзакций. Данный класс не является threadsafe, но является safe
относительно совместного использования между разными функциями. Стандартное
применение предполагает получение интрузивного птр в каждом методе контроллера,
заполнение его при помощи FillSharedTransaction, чтобы гарантировать наличие
какое-либо транзакции. По умолчанию выполняется коммит в деструкторе, чтобы
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
        transaction = ::utils::MakeSharedTransaction(
            ptr, name, auto_commit);
    }
}
}  // namespace utils
