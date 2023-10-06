#pragma once

#include <cstddef>
#include <openapi/base/doc.hpp>
#include <string_view>
namespace timetable_vsu_backend::openapi
{
inline void RemoveRequests(Doc& doc)
{
    auto root = doc().ExtractValue();
}
}  // namespace timetable_vsu_backend::openapi
