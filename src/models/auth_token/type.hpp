#pragma once
#include <boost/uuid/uuid.hpp>

namespace timetable_vsu_backend::models{
    struct AuthToken{
        boost::uuids::uuid id;
    };
}