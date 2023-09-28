#pragma once

//обманываем систему с if constexpr
#define STATIC_ASSERT_FALSE(msg) \
    static_assert(               \
        ![]() {}, msg)
