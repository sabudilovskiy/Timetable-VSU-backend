#pragma once
#include "base.hpp"

namespace std {
template <typename T>
class optional;
}

namespace timetable_vsu_backend::utils::convert {
template <typename T, ConstexprString name>
using OptionalProperty =
    BaseProperty<std::optional<T>, name, RequestParse::Unspecified>;
}