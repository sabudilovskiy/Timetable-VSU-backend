#pragma once
#include <optional>
#include <string>
#include <utils/convert/additional_properties.hpp>
#include <utils/convert/base.hpp>

#include "models/user_credentials/type.hpp"
#include "models/user_type/type.hpp"
namespace timetable_vsu_backend::models
{
using namespace utils::convert;
struct RegisterRequest
{
    Property<models::UserCredentials, "user_credentials"> user_credentials;
    OptionalProperty<std::string, "description"> description;
    OptionalProperty<UserType, "desired_type"> desired_type;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
