#pragma once
#include <openapi/base/named_traits.hpp>
#include <openapi/base/reflective_utils.hpp>
#include <openapi/doc/serialize/base.hpp>
#include <openapi/http/base/body_property.hpp>
#include <type_traits>
#include <userver/formats/yaml/types.hpp>
#include <userver/formats/yaml/value_builder.hpp>
#include <userver/utils/meta.hpp>
#include <userver/utils/overloaded.hpp>

namespace timetable_vsu_backend::openapi
{
template <checks::IsReflective T>
void AppendRequest(DocHelper doc_helper, std::type_identity<T>)
{
    auto& [root, cur] = doc_helper;
    cur["description"] = GetOpenApiTypeName<T>();
    CallAllFields<T>(
        [doc_helper](auto field) { AppendRequestField(doc_helper, field); });
}
}  // namespace timetable_vsu_backend::openapi
