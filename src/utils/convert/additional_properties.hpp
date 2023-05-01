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

template <typename U>
concept IsArray = requires {
    typename U::value_type;
    requires std::is_same_v<std::vector<typename U::value_type>, U>;
};

template <typename T>
concept IsOptionalProperty = requires {
    requires std::is_class_v<T>;
    typename T::value_type;
    typename T::value_type::value_type;
    requires std::is_same_v<
        OptionalProperty<typename T::value_type::value_type, T::kName>, T>;
    requires !IsArray<typename T::value_type::value_type>;
};

//Оригинальный тип, спрятанный под OptionalProperty
template <IsOptionalProperty T>
using optional_property_t = typename T::value_type::value_type;

template <typename T, ConstexprString name>
using ArrayProperty =
    BaseProperty<std::vector<T>, name, RequestParse::Unspecified>;

//Оригинальный тип, спрятанный под ArrayProperty
template <typename T>
concept IsArrayProperty = requires {
    requires std::is_class_v<T>;
    typename T::value_type;
    typename T::value_type::value_type;
    requires std::is_same_v<
        ArrayProperty<typename T::value_type::value_type, T::kName>, T>;
};

template <IsArrayProperty T>
using array_property_t = typename T::value_type::value_type;

template <typename T, ConstexprString name>
using OptionalArrayProperty = BaseProperty<std::optional<std::vector<T>>, name,
                                           RequestParse::Unspecified>;

template <typename T>
concept IsOptionalArrayProperty = requires {
    requires std::is_class_v<T>;
    typename T::value_type;
    typename T::value_type::value_type;
    typename T::value_type::value_type::value_type;
    requires std::is_same_v<
        OptionalArrayProperty<typename T::value_type::value_type::value_type,
                              T::kName>,
        T>;
};

//Оригинальный тип, спрятанный под OptionalArrayProperty
template <IsOptionalArrayProperty T>
using optional_array_property_t =
    typename T::value_type::value_type::value_type;

//концепт проверяет, является ли свойство структурным, то есть несёт в себе
//структуру, которую так же необходимо разложить
template <typename T>
concept IsStructuralProperty = requires {
    requires IsAnyProperty<T>;
    requires IsConvertAll<typename T::value_type>;
};

//данный концепт является костылём, он определяет, что поле является "обычным"
//свойством, то есть не требует дополнительных действий
template <typename T>
concept IsUsualProperty =
    IsAnyProperty<T> && !IsOptionalProperty<T> && !IsOptionalArrayProperty<T> &&
    !IsArrayProperty<T> && !IsStructuralProperty<T>;

}  // namespace timetable_vsu_backend::utils::convert