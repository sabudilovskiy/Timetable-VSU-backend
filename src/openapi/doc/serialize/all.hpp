#pragma once
#include <boost/pfr/core.hpp>
#include <boost/pfr/tuple_size.hpp>
#include <cctype>
#include <concepts>
#include <cstdint>
#include <experimental/source_location>
#include <iostream>
#include <source_location>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <userver/compiler/demangle.hpp>
#include <userver/formats/common/type.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/yaml/serialize.hpp>
#include <userver/formats/yaml/value_builder.hpp>
#include <userver/logging/log.hpp>
#include <userver/utils/checked_pointer.hpp>
#include <userver/utils/overloaded.hpp>
#include <utility>

#include "openapi/base/array_property.hpp"
#include "openapi/base/array_traits.hpp"
#include "openapi/base/doc.hpp"
#include "openapi/base/object_property.hpp"
#include "openapi/base/object_traits.hpp"
#include "openapi/base/optional_property.hpp"
#include "openapi/base/reflective_preferences.hpp"
#include "openapi/base/string_property.hpp"
#include "openapi/base/string_traits.hpp"
#include "utils/compilers_macros.hpp"

namespace timetable_vsu_backend::openapi
{
inline void log_yaml_impl(userver::formats::yaml::ValueBuilder yaml,
                          std::string_view file_name, int line,
                          std::string_view function_name)
{
    std::clog << "=======================\n";
    std::clog << file_name << "(" << line << ") " << function_name << "\n";
    std::clog << "====================\n";
    std::clog << ToString(yaml.ExtractValue()) << '\n';
}

#define log_yaml(yaml)                                                      \
    timetable_vsu_backend::openapi::log_yaml_impl(yaml, __FILE__, __LINE__, \
                                                  __PRETTY_FUNCTION__)

inline void RemoveNamespaces(std::string& name_class)
{
    auto write = name_class.begin();
    auto read = name_class.begin();
    *write = toupper(*read);
    write++;
    read++;
    while (read != name_class.end())
    {
        if (*read == ':' || *read == '_')
        {
            while (read != name_class.end() && (*read == ':' || *read == '_'))
            {
                read++;
            }
            if (read != name_class.end())
            {
                *write = toupper(*read);
                write++;
                read++;
            }
        }
        else
        {
            *write = *read;
            write++;
            read++;
        }
    }
    name_class.resize(write - name_class.begin());
}
//это нужно для:
// 1) явного переопределения названий классов в рамках опенапи
// 2) написания какой-то логики преобразований
template <typename T>
std::string GetOpenApiTypeName()
{
    std::string raw_name = userver::compiler::GetTypeName<T>();
    if (raw_name.find_first_of('<') != std::string::npos ||
        raw_name.find_first_of('>') != std::string::npos)
    {
        throw std::runtime_error(fmt::format(
            "template in name type: {}, overload this function", raw_name));
    }
    RemoveNamespaces(raw_name);
    return raw_name;
}

template <typename T>
void PlaceRefToType(userver::formats::yaml::ValueBuilder& place)
{
    if (!place.IsObject())
    {
        place = userver::formats::common::Type::kObject;
    }
    auto ref_str =
        std::string(R"(#/components/schemas/)").append(GetOpenApiTypeName<T>());
    std::clog << "log this moment: 104\n";
    place["$ref"] = std::move(ref_str);
}

template <typename T, typename... Other>
consteval bool IsAnyOf()
{
    return (std::same_as<T, Other> || ...);
}

template <typename T>
concept IsDefaultOpenApiType = requires
{
    requires IsAnyOf<T, std::string>() || std::is_integral_v<T>;
};
using StringMap = std::unordered_map<std::string, std::string>;

struct DocHelper
{
    userver::formats::yaml::ValueBuilder& root;
    userver::formats::yaml::ValueBuilder& cur_place;
};

inline void log_dock_helper_impl(DocHelper doc_helper,
                                 std::string_view file_name, int line,
                                 std::string_view function_name)
{
    std::clog << "=======================\n";
    std::clog << file_name << "(" << line << ") " << function_name << "\n";
    std::clog << "====================\n";
    auto [cur_place, root] = doc_helper;

    std::clog << ToString(root.ExtractValue()) << '\n';
}

template <typename T>
void Append(DocHelper, std::type_identity<T>)
{
    STATIC_ASSERT_FALSE("You use unknowned type");
}

template <typename T, typename Traits>
void Append(DocHelper doc_helper,
            std::type_identity<ObjectProperty<T, Traits>> = {})
{
    Append(doc_helper, std::type_identity<T>{});
}

template <typename T, typename Traits>
void Append(DocHelper doc_helper,
            std::type_identity<ArrayProperty<T, Traits>> = {})
{
    constexpr traits::ArrayHelperTraits<Traits> traits;
    auto& field_node = doc_helper.cur_place;
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "array";
    if constexpr (traits.min.HasValue())
    {
        field_node["min"] = traits.min.value();
    }
    if constexpr (traits.max.HasValue())
    {
        field_node["max"] = traits.max.value();
    }
    if constexpr (traits.unique_items.value_or(false))
    {
        field_node["unique_item"] = true;
    }
    auto items_node = field_node["items"];
    Append(DocHelper{doc_helper.root, items_node}, std::type_identity<T>{});
}

template <typename Traits>
void Append(DocHelper doc_helper,
            std::type_identity<StringProperty<Traits>> = {})
{
    constexpr traits::StringHelperTraits<Traits> traits;
    auto& field_node = doc_helper.cur_place;
    if (!field_node.IsObject())
        field_node = userver::formats::common::Type::kObject;
    field_node["type"] = "string";
    if constexpr (!traits.pattern.empty())
    {
        field_node["pattern"] = std::string{traits.pattern.AsStringView()};
    }
}

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

template <typename... Field>
void AppendFields(DocHelper doc_helper,
                  std::type_identity<std::tuple<Field...>>)
{
    (AppendField<Field>(doc_helper), ...);
}

template <checks::IsReflective T>
auto MakeSequence()
{
    return std::make_index_sequence<boost::pfr::tuple_size<T>::value>();
}

template <typename T, size_t... I>
void AppendFields(DocHelper doc_helper, std::type_identity<T>,
                  std::integer_sequence<size_t, I...>)
{
    using Type =
        std::tuple<std::remove_cvref_t<boost::pfr::tuple_element_t<I, T>>...>;
    AppendFields(doc_helper, std::type_identity<Type>{});
}

template <checks::IsReflective T>
void AppendFields(DocHelper doc_helper, std::type_identity<T>)
{
    auto sequence = MakeSequence<T>();
    AppendFields(doc_helper, std::type_identity<T>{}, sequence);
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
        AppendFields(DocHelper{doc_helper.root, type_node},
                     std::type_identity<T>{});
    }
}

template <checks::IsReflective T>
void Append(Doc& doc, std::type_identity<T>)
{
    auto& root = doc.value_;
    Append(DocHelper{root, root}, std::type_identity<T>{}, false);
}
}  // namespace timetable_vsu_backend::openapi
