#pragma once
#include <openapi/base/reflective_utils.hpp>
#include <openapi/doc/serialize/base.hpp>
#include <type_traits>

namespace timetable_vsu_backend::openapi
{
template <typename T>
void AppendField(DocHelper doc_helper, std::type_identity<T> type = {})
{
    using Traits = typename T::traits;
    constexpr auto name_ce = traits::GetName<Traits>();
    constexpr auto name_ce_empty = name_ce.empty();
    static_assert(!name_ce_empty, "Field must have name");
    std::string name{name_ce.AsStringView()};
    auto field_node = doc_helper.cur_place["properties"][name];
    auto matcher = userver::utils::Overloaded{
        [&]<typename U>(std::type_identity<U>) {
            auto required = doc_helper.cur_place["required"];
            if (!required.IsArray())
                required = userver::formats::common::Type::kArray;
            required.PushBack(name);
        },
        []<typename U, typename Traits>(
            std::type_identity<OptionalProperty<U, Traits>>) {}};
    matcher(type);
    Append(DocHelper{doc_helper.root, field_node}, std::type_identity<T>{});
}

// noop, пропускаем
template <>
inline void AppendField(DocHelper, std::type_identity<AdditionalProperties>)
{
}

template <checks::IsReflective T>
void Append(DocHelper doc_helper, std::type_identity<T>,
            bool append_cur_place = true)
{
    std::string name_type = GetOpenApiTypeName<T>();
    if (append_cur_place)
    {
        PlaceRefToType<T>(doc_helper.cur_place);
    }
    auto type_node = doc_helper.root["components"]["schemas"][name_type];
    if (!type_node.IsObject())
    {
        type_node = userver::formats::common::Type::kObject;
        type_node["type"] = "object";
        constexpr checks::ReflectivePreferences<T> pref{};
        bool additional_properties = (pref.additional_properties_status ==
                                      checks::AdditionalPropertiesStatus::True);
        type_node["additionalProperties"] = additional_properties;
        auto dock_helper = DocHelper{doc_helper.root, type_node};
        auto visiter_fields = [dock_helper](auto field) {
            AppendField(dock_helper, field);
        };
        CallAllFields<T>(visiter_fields);
    }
}

template <checks::IsReflective T>
void Append(Doc& doc, std::type_identity<T>)
{
    auto& root = doc.value_;
    Append(DocHelper{root, root}, std::type_identity<T>{}, false);
}

}  // namespace timetable_vsu_backend::openapi
