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

namespace views::test::login
{
namespace
{
using Resp200 = Resp<Response, 200>;
using Resp400 = Resp<Response, 400>;
struct View final
    : public openapi::http::OpenApiHandler<Request, Resp200, Resp400>
{
    static constexpr std::string_view kName = "test-login-view";
    using Base = openapi::http::OpenApiHandler<Request, Resp200, Resp400>;
    View(const userver::components::ComponentConfig& cfg,
         const userver::components::ComponentContext& ctx)
        : Base(cfg, ctx)
    {
    }
    Resps Handle(Request&&) const override
    {
        Resp200 resp200;
        return resp200;
    }
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<View>();
}

}  // namespace views::test::login
