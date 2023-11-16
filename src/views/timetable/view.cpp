#include "view.hpp"

#include <fmt/format.h>

#include <chrono>
#include <exception>
#include <openapi/all.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/initialize_dependents.hpp>

#include "controllers/lesson/controller.hpp"
#include "controllers/token/controller.hpp"
#include "controllers/user/controller.hpp"
#include "declarations.hpp"

namespace views::timetable
{
namespace
{
using Resp200 = Resp<Response, 200>;
using Base = openapi::http::OpenApiHandler<"timetable-view", Request, Resp200>;

struct Dependends
{
    controllers::lesson::Controller& lesson_controller;
};
struct View final : Base
{
    View(const userver::components::ComponentConfig& cfg,
         const userver::components::ComponentContext& ctx)
        : Base(cfg, ctx),
          dependends_(utils::initialize_dependends<Dependends>(ctx))
    {
    }
    Resps Handle(Request&& req) const override
    {
        auto& filter = req.body().filter();
        LOG_DEBUG() << "parsed: "
                    << ToString(userver::formats::json::ValueBuilder(filter)
                                    .ExtractValue());
        Resp200 resp200;
        resp200().body().lessons() =
            dependends_.lesson_controller.FindLessons(filter);
        return resp200;
    }

   protected:
    Dependends dependends_;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<View>();
}

}  // namespace views::timetable
