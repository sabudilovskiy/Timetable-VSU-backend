#pragma once
#include <boost/pfr/core.hpp>
#include <openapi/base/named_traits.hpp>
#include <openapi/base/object_property.hpp>
#include <openapi/http/base/body.hpp>
#include <openapi/http/base/cookie_property.hpp>
#include <openapi/http/base/header_property.hpp>
#include <openapi/http/base/response_info.hpp>
#include <openapi/http/base/response_property.hpp>
#include <openapi/http/base/status_code.hpp>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/utils/meta.hpp>
#include <userver/utils/overloaded.hpp>
#include <utils/compilers_macros.hpp>
#include <utils/formated_exception.hpp>

namespace openapi::http
{
template <checks::IsReflective T, typename Traits>
ResponseInfo Serialize(const ResponseProperty<T, Traits>& item,
                       userver::formats::serialize::To<ResponseInfo>)
{
    ResponseInfo result{};
    result.userver_code = Traits::code;
    auto matcher_header = [&]<typename H, typename HTraits>(
                              const HeaderProperty<H, HTraits>& hitem) {
        constexpr auto name = traits::GetName<HTraits>();
        static_assert(!name.empty(), "header must have name");
        std::string name_str = name.AsString();
        std::optional<std::string> header_value;
        if constexpr (std::is_same_v<std::optional<std::string>, H> ||
                      std::is_same_v<std::string, H>)
        {
            header_value = hitem();
        }
        else if constexpr (userver::meta::kIsOptional<H>)
        {
            if (hitem().has_value())
            {
                header_value =
                    Serialize(hitem().value(),
                              userver::formats::serialize::To<std::string>{});
            }
        }
        else
        {
            header_value = Serialize(
                hitem(), userver::formats::serialize::To<std::string>{});
        }
        if (header_value)
        {
            result.headers.try_emplace(name_str,
                                       std::move(header_value.value()));
        }
    };
    auto matcher_cookie =
        [&]<typename C, typename CTraits>(const CookieProperty<C, CTraits>&) {
            STATIC_ASSERT_FALSE(
                "Openapi doesnt support cookie in responses. Sorry :(");
        };
    auto matcher_json_body = [&]<typename B, typename BTraits>(
                                 const BodyProperty<B, BTraits>& bitem) {
        result.response_body_type = ResponseBodyType::kJson;
        result.body = ToString(Serialize(
            bitem(),
            userver::formats::serialize::To<userver::formats::json::Value>{}));
    };
    auto matcher_all = userver::utils::Overloaded{std::move(matcher_header),
                                                  std::move(matcher_json_body),
                                                  std::move(matcher_cookie)};
    boost::pfr::for_each_field(item(), std::move(matcher_all));
    return result;
}
}  // namespace openapi::http
