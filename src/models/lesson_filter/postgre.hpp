#include <userver/storages/postgres/io/composite_types.hpp>

#include "models/lesson_filter/type.hpp"
namespace userver::storages::postgres::io {
template <>
struct CppToUserPg<timetable_vsu_backend::models::LessonFilter> {
    static constexpr DBTypeName postgres_name = "cart.cart_item_v14";
};
}  // namespace userver::storages::postgres::io