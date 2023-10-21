#pragma once
#include <openapi/base/holder.hpp>
#include "utils/constexpr_string.hpp"

namespace openapi::types{
    namespace detail{
        struct DatetimeHolder{
            traits::HolderField<utils::FixedString> name;
        };

        
    }   
}