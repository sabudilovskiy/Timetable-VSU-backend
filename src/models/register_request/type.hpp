#pragma once
#include <string>

#include "models/user_credentials/type.hpp"
#include "models/user_type/type.hpp"
#include "utils/convert/base.hpp"
namespace timetable_vsu_backend::models
{
using namespace utils::convert;
struct RegisterRequest
{
    Property<models::UserCredentials, "user_credentials"> user_credentials;
    Property<std::string, "description"> description;
    Property<UserType, "desired_type"> desired_type;
    static constexpr TypeOfBody kTypeOfBody =
        TypeOfBody::Json;  //открываем возможность использовать структуру, как
                           //запрос
    static constexpr PolicyFields kPolicyFields = PolicyFields::ConvertAll;
};
}  // namespace timetable_vsu_backend::models
