#pragma once

#define STATIC_ASSERT_FALSE(msg) \
    static_assert(               \
        ![]() {}, msg)
