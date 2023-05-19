#pragma once
#include <chrono>
#include <userver/utils/strong_typedef.hpp>
namespace timetable_vsu_backend::models
{
using TimeString =
    userver::utils::StrongTypedef<struct TimeStringTag,
                                  std::chrono::system_clock::time_point>;
}
