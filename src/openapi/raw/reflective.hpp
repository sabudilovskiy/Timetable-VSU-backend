#pragma once

#include "boost/pfr/core.hpp"
#include "openapi/base/object_property.hpp"

namespace timetable_vsu_backend::openapi::raw{
    template <checks::IsReflective T>
    struct Raw{
        using mut_tie = decltype(boost::pfr::tie_from_structure(std::declval<T&>()));
        using const_tie = decltype(boost::pfr::tie_from_structure(std::declval<T&>()));
        static auto ResolveMutType(){
            
        }
        static auto ResolveConstType(){
            
        }
    };
}