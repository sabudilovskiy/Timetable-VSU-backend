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

namespace openapi
{
template <checks::IsReflective T>
void AppendResponse(Doc& doc, std::type_identity<T>)
{
    auto& root = doc.value_;
    userver::formats::yaml::ValueBuilder response =
        root["components"]["responses"][GetOpenApiTypeName<T>()];
    if (response.IsObject())
    {
        return;
    }
    auto description = response["description"];
    description = "";
    auto doc_helper = DocHelper{root, response};
    CallAllFields<T>(
        [doc_helper](auto field) { AppendResponseField(doc_helper, field); });
}
}  // namespace openapi
