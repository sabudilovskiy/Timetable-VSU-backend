#pragma once
#include "common_errors.hpp"
namespace timetable_vsu_backend::utils::common_errors
{
[[nodiscard]] Response400 PerformLoginTaken();

[[nodiscard]] Response401 PerformInvalidToken();

[[nodiscard]] Response403 PerformForbidden();

[[nodiscard]] Response400 PerformInvalidData(std::string_view message);
}  // namespace timetable_vsu_backend::utils::common_errors
