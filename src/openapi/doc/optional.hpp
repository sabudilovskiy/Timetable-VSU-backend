#pragma once
#include <openapi/doc/base.hpp>

namespace openapi
{
template <typename T, typename Traits>
void Append(DocHelper doc_helper,
            std::type_identity<OptionalProperty<T, Traits>> = {})
{
    Append(doc_helper, std::type_identity<T>{});
}
}  // namespace openapi
