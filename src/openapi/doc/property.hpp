#pragma once
#include <openapi/doc/base.hpp>

namespace openapi
{
template <typename T>
requires IsProperty<T> void Append(DocHelper doc_helper,
                                   std::type_identity<T> = {})
{
    Append(doc_helper, std::type_identity<typename T::value_type>{});
}
}  // namespace openapi
