#pragma once
#include <string>
#include <userver/formats/parse/to.hpp>

#include "userver/formats/common/meta.hpp"
#include "userver/server/http/http_request.hpp"
#include "utils/convert/base.hpp"
#include "utils/convert/http_request_parse.hpp"
#include "utils/convert/json_parse.hpp"

namespace timetable_vsu_backend::views::login {
using namespace utils::convert;
struct Request {
  Property<std::string, "login"> login;
  Property<std::string, "password"> password;
  static constexpr TypeOfBody kTypeOfBody = TypeOfBody::Json;
  static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::views::login