#pragma once

#include <cstddef>
namespace timetable_vsu_backend::openapi::http{
    template <std::size_t Code>
    struct ResponseTraits{
        static constexpr auto code = Code;
    };
}