#pragma once
#include <chrono>
#include <userver/utils/strong_typedef.hpp>
namespace models
{
using TimeString =
    userver::utils::StrongTypedef<struct TimeStringTag,
                                  std::chrono::system_clock::time_point>;
}
