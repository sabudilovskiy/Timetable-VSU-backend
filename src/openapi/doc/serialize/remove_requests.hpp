#pragma once

#include <cstddef>
#include <openapi/base/doc.hpp>
#include <string_view>
namespace openapi
{
inline void RemoveRequests(Doc& doc)
{
    auto root = doc().ExtractValue();
}
}  // namespace openapi
