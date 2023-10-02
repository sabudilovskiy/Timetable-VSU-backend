#pragma once

#include <cstddef>
#include <string_view>
#include "openapi/base/doc.hpp"
namespace timetable_vsu_backend::openapi
{
    inline void RemoveRequests(Doc& doc){
        auto root = doc().ExtractValue();
       
    }
}

