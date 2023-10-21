#pragma once
#include <boost/pfr/core.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/properties/object.hpp>
#include <openapi/http/base/body.hpp>
#include <openapi/http/base/cookie_property.hpp>
#include <openapi/http/base/header_property.hpp>
#include <openapi/http/base/request_info.hpp>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/utils/meta.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/formated_exception.hpp>

namespace openapi::http
{
template <typename T>
requires checks::is_reflective_v<T> T Parse(const RequestInfo& info,
                                            userver::formats::parse::To<T>)
{
    T t;
    auto matcher_header = [&]<typename H, typename Traits>(
                              HeaderProperty<H, Traits>& item) {
        constexpr auto name = traits::GetName<Traits>();
        static_assert(!name.empty(), "header must have name");
        std::string_view name_sv = name.AsStringView();
        auto it = info.headers.find(name_sv);
        if (it == info.headers.end())
        {
            if constexpr (!userver::meta::kIsOptional<H>)
            {
                throw utils::formated_exception("Missing header: {}", name_sv);
            }
            else
                return;
        }
        const std::string& founded = it->second;
        if constexpr (std::is_same_v<std::string, H> ||
                      std::is_same_v<std::optional<std::string>, H>)
        {
            item() = founded;
        }
        else
        {
            item() = Parse(founded, userver::formats::parse::To<H>{});
        }
    };
    auto matcher_cookie = [&]<typename C, typename Traits>(
                              CookieProperty<C, Traits>& item) {
        constexpr auto name = traits::GetName<Traits>();
        static_assert(!name.empty(), "cookie must have name");
        std::string name_sv = name.AsString();
        auto it = info.cookies.find(name_sv);
        if (it == info.cookies.end())
        {
            if constexpr (!userver::meta::kIsOptional<C>)
            {
                throw utils::formated_exception("Missing cookie: {}", name_sv);
            }
            else
                return;
        }
        const std::string& founded = it->second;
        if constexpr (std::is_same_v<std::string, C> ||
                      std::is_same_v<std::optional<std::string>, C>)
        {
            item() = founded;
        }
        else
        {
            item() = Parse(founded, userver::formats::parse::To<C>{});
        }
    };
    auto matcher_json_body =
        [&]<typename B, typename Traits>(BodyProperty<B, Traits>& item) {
            auto json = userver::formats::json::FromString(info.body);
            item() = Parse(json, userver::formats::parse::To<B>{});
        };
    auto matcher_all = userver::utils::Overloaded{std::move(matcher_header),
                                                  std::move(matcher_cookie),
                                                  std::move(matcher_json_body)};
    boost::pfr::for_each_field(t, std::move(matcher_all));
    return t;
}
}  // namespace openapi::http
