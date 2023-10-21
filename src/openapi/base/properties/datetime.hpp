#pragma once
#include <chrono>
#include <compare>
#include <openapi/base/property_base.hpp>
#include <userver/storages/postgres/io/chrono.hpp>

namespace openapi
{
template <typename Traits>
struct DateTimeProperty
    : PropertyBase<userver::storages::postgres::TimePointTz, Traits>
{
};

template <typename Traits>
struct types::Property<userver::storages::postgres::TimePointTz, Traits>
    : DateTimeProperty<Traits>
{
};
}  // namespace openapi
