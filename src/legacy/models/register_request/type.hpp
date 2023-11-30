#pragma once
#include <optional>
#include <string>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>

#include "legacy/models/user_credentials/type.hpp"
#include "legacy/models/user_type/type.hpp"
namespace legacy::models
{
using namespace utils::convert;
struct RegisterRequest
{
    Property<legacy::models::UserCredentials, "user_credentials">
        user_credentials;
    OptionalProperty<std::string, "description"> description;
    OptionalProperty<UserType, "desired_type"> desired_type;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
};
}  // namespace legacy::models
