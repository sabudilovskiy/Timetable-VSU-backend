#pragma once
#include <boost/uuid/uuid.hpp>
#include <utility>

#include "models/user_credentials/type.hpp"
#include "userver/formats/json/value.hpp"
#include "utils/convert/base.hpp"
#include "utils/convert/http_request_parse.hpp"
#include "utils/convert/json_parse.hpp"
#include "utils/parse/uuid/string.hpp"
namespace timetable_vsu_backend::views::root::create_admin {
using namespace utils::convert;
struct Request {
    Property<models::UserCredentials, "credentials"> credentials;
    HeaderProperty<boost::uuids::uuid, "token"> token;
    static constexpr auto kPolicyFields = PolicyFields::ConvertAll;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
};
// void test(){
//    Request request;
//    userver::server::http::HttpRequest* test;
//    userver::formats::json::Value* test2;
//    request.token = Parse(std::string{},
//    userver::formats::parse::To<decltype(request.token)::value_type>{});
//    // detail::parse::ConverterHttpRequest<Request>::ParseField(*test, *test2,
//    request.token);
// }
}  // namespace timetable_vsu_backend::views::root::create_admin
