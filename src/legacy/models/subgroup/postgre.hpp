#pragma once
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using ::legacy::models::Subgroup;
template <>
struct CppToUserPg<Subgroup> : EnumMappingBase<Subgroup>
{
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        "timetable_vsu.subgroup";
    static constexpr userver::utils::TrivialBiMap enumerators =
        [](auto selector) {
            return selector()
                .Case("all", Subgroup::kAll)
                .Case("first", Subgroup::kFirst)
                .Case("second", Subgroup::kSecond);
        };
};
}  // namespace userver::storages::postgres::io
