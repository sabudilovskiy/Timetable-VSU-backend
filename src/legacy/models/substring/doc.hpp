#pragma once

#include <legacy/models/substring/type.hpp>
#include <openapi/doc/base.hpp>
#include <type_traits>
namespace openapi
{
inline void Append(DocHelper doc_helper,
                   std::type_identity<legacy::models::SubString>)
{
    doc_helper.cur_place["type"] = "string";
}
}  // namespace openapi
