#pragma once
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using ::models::EducationType;
template <>
struct CppToUserPg<EducationType> : EnumMappingBase<EducationType>
{
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        "timetable_vsu.grouptype";
    static constexpr userver::utils::TrivialBiMap enumerators =
        [](auto selector) {
            return selector()
                .Case("magistracy", EducationType::kMagistracy)
                .Case("postgraduate", EducationType::kPostgraduate)
                .Case("undergraduate", EducationType::kUndergraduate)
                .Case("specialty", EducationType::kSpecialty);
        };
};
}  // namespace userver::storages::postgres::io
