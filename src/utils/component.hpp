#pragma once

#pragma once

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <utils/constexpr_string.hpp>
namespace utils
{
template <ConstexprString Name>
struct Component : public userver::components::LoggableComponentBase
{
    [[maybe_unused]] static constexpr auto kName = Name.AsStringView();
    Component(const userver::components::ComponentConfig& cfg,
              const userver::components::ComponentContext& ctx)
        : userver::components::LoggableComponentBase(cfg, ctx)
    {
    }
};
}  // namespace utils
