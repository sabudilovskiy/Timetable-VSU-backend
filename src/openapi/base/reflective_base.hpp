#pragma once
#include <boost/pfr.hpp>
#include <boost/pfr/core.hpp>
#include <concepts>
#include <type_traits>

namespace timetable_vsu_backend::openapi
{
struct Yes
{
};

#define REFLECTIVE_BASE(Type)                               \
   private:                                                 \
    void _Assert_right_type()                               \
    {                                                       \
        using This = std::remove_cvref_t<decltype(*this)>;  \
        static_assert(std::is_same_v<This, Type>,           \
                      "You are using the wrong type");      \
    }                                                       \
                                                            \
   public:                                                  \
    using Reflective = timetable_vsu_backend::openapi::Yes; \
    auto operator<=>(const Type&) const = default
}  // namespace timetable_vsu_backend::openapi
