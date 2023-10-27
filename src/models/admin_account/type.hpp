#pragma once
#include <openapi/types/string.hpp>
#include <openapi/types/uuid.hpp>

namespace models{
    using namespace openapi::types;
    using namespace openapi::preferences;
    struct AdminAccount
    {
        Uuid<Name<"user_id">> user_id;
        Uuid<Name<"admin_id">> admin_id;
        String<Name<"login">> credentials;
        auto operator<=>(const AdminAccount&) const = default;
    };
}