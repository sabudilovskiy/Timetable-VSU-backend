#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <utils/component_list_fwd.hpp>
#include <utils/pg_controller.hpp>
#include <utils/shared_transaction.hpp>

#include "models/lesson_filter/type.hpp"
#include "models/lesson_v1/type.hpp"

namespace controllers::lesson
{
using Base = utils::PgController<"new-lesson-controller", "postgres-db-1">;
struct Controller : Base
{
    Controller(const userver::components::ComponentConfig& cfg,
               const userver::components::ComponentContext& ctx);
    std::vector<models::LessonV1> FindLessons(
        const std::optional<models::LessonFilter>& filter,
        utils::SharedTransaction transaction = nullptr) const;
};
}  // namespace controllers::lesson
