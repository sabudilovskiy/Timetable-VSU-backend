#pragma once
#include <userver/storages/postgres/io/enum_types.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io {
using timetable_vsu_backend::models::UserType;
template <>
struct CppToUserPg<UserType> : EnumMappingBase<UserType> {
    static constexpr userver::storages::postgres::DBTypeName postgres_name =
        "vsu_timetable.usertype";
    static constexpr userver::utils::TrivialBiMap enumerators =
        [](auto selector) {
            return selector()
                .Case("user", UserType::kUser)
                .Case("admin", UserType::kAdmin)
                .Case("root", UserType::kRoot)
                .Case("teacher", UserType::kTeacher);
        };
};
}  // namespace userver::storages::postgres::io