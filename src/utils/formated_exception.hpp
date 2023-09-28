#include <fmt/format.h>

#include <exception>
#include <stdexcept>
#include <utility>

namespace timetable_vsu_backend::utils
{
/*
Небольшая обёртка, чтобы не писать каждый раз fmt::format()
*/
struct formated_exception : std::runtime_error
{
    /*
        конструктор форвардит внутрь фмт формат
    */
    template <typename... T>
    formated_exception(fmt::format_string<T...> fmt, T&&... args)
        : std::runtime_error(fmt::format(fmt, std::forward<T>(args)...))
    {
    }
};
}  // namespace timetable_vsu_backend::utils
