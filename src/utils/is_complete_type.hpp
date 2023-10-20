#pragma once

namespace utils
{
template <typename T>
concept is_complete_type = requires(T* t)
{
    sizeof(*t);
};
}  // namespace utils
