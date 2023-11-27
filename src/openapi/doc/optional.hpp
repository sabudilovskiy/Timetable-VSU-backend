#pragma once
#include <openapi/base/properties/optional.hpp>
#include <openapi/doc/base.hpp>

namespace openapi
{
template <typename T, auto Traits>
void Append(DocHelper doc_helper,
            std::type_identity<OptionalProperty<T, Traits>> = {})
{
    Append(doc_helper, std::type_identity<T>{});
}
}  // namespace openapi
