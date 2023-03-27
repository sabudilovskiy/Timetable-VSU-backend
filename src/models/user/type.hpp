#pragma once
#include <boost/uuid/uuid.hpp>
#include <userver/utils/strong_typedef.hpp>
#include "../user_type/type.hpp"

namespace timetable_vsu_backend::models{
    struct User{
        using Id = userver::utils::StrongTypedef<struct IdTag, boost::uuids::uuid>;
        Id id;
        std::string login;
        std::string password;
        UserType user_type;
    };
}