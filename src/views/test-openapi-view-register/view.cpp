#include "view.hpp"

#include <chrono>
#include <exception>
#include <openapi/all.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>

#include "declarations.hpp"

namespace timetable_vsu_backend::views::test::sign_in
{
namespace
{
using Resp200 = Resp<Response, 200>;
struct View final : openapi::http::OpenApiHandler<Request, Resp200>
{
    static constexpr std::string_view kName = "test-register-view";
    using Base = openapi::http::OpenApiHandler<Request, Resp200>;
    View(const userver::components::ComponentConfig& cfg,
         const userver::components::ComponentContext& ctx)
        : Base(cfg, ctx)
    {
    }
    Resps Handle(Request&& req) const override
    {
        Resp200 resp200;
        resp200().body().some_string() =
            fmt::format("login: {}, password: {}", req.body().login(),
                        req.body().password());
        resp200().some_header() = req.some_token().value_or("empty");
        return resp200;
    }
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<View>();
}

}  // namespace timetable_vsu_backend::views::test::sign_in
