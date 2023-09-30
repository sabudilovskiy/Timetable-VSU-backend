#pragma once

#include <cstddef>
#include <openapi/http/base/status_code.hpp>
namespace timetable_vsu_backend::openapi::http
{
template <std::size_t CodeInt>
struct ResponseTraits
{
    static constexpr auto code = code_v<CodeInt>;
};
}  // namespace timetable_vsu_backend::openapi::http
