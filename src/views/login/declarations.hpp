#pragma once
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <openapi/all.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/storages/postgres/io/io_fwd.hpp>

#include "legacy/models/user_type/doc.hpp"
#include "legacy/models/user_type/parse.hpp"
#include "legacy/models/user_type/postgre.hpp"
#include "legacy/models/user_type/serialize.hpp"
#include "models/user/type.hpp"
#include "models/user_credentials/type.hpp"

using namespace openapi::types;
using namespace openapi::http;
using namespace openapi::preferences;
namespace views::login
{
struct Request
{
    Body<models::UserCredentials> body;
    auto operator<=>(const Request&) const = default;
};

struct ResponseBody
{
    Object<models::User, Name<"user">> user;
    Uuid<Name<"token">> token;
    auto operator<=>(const ResponseBody&) const = default;
};

struct Response
{
    Body<ResponseBody> body;
    auto operator<=>(const Response&) const = default;
};

}  // namespace views::login