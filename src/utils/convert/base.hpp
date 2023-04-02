#pragma once
#include <type_traits>
#include <utility>
// #include "utlis/convert/constexpr_string.hpp"
#include "../constexpr_string.hpp"

namespace timetable_vsu_backend::utils::convert {
//В данный момент поддерживаются только конвертация всех полей
enum struct PolicyFiels { ConvertAll };

//влом больше поддерживать
enum struct TypeOfBody { Empty, Json };

template <PolicyFiels policy_fields>
struct ConvertBase {
  constexpr auto static kPolicyFields = policy_fields;
};

template <typename T>
concept IsConvertAll =
    std::is_same_v<decltype(T::kPolicyFields), const PolicyFiels> &&
    T::kPolicyFields == PolicyFiels::ConvertAll;

template <typename T, ConstexprString name>
struct Property {
  using value_type = T;
  constexpr auto static kName = name;

  template <class Arg>
  value_type& operator=(Arg&& arg) {
    value = std::forward<Arg>(arg);
    return value;
  }
  value_type value;
};

template <typename T, ConstexprString name>
struct QueryProperty {
  using value_type = T;
  constexpr auto static kName = name;

  template <class Arg>
  value_type& operator=(Arg&& arg) {
    value = std::forward<Arg>(arg);
    return value;
  }
  value_type value;
};

template <typename T, ConstexprString name>
struct HeaderProperty {
  using value_type = T;
  constexpr auto static kName = name;

  template <class Arg>
  value_type& operator=(Arg&& arg) {
    value = std::forward<Arg>(arg);
    return value;
  }
  value_type value;
};

template <typename T, ConstexprString name>
struct CookieProperty {
  using value_type = T;
  constexpr auto static kName = name;

  template <class Arg>
  value_type& operator=(Arg&& arg) {
    value = std::forward<Arg>(arg);
    return value;
  }
  value_type value;
};

template <typename T>
concept IsProperty = std::is_class_v<T> &&
    std::is_same_v<Property<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsQueryProperty = std::is_class_v<T> &&
    std::is_same_v<QueryProperty<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsHeaderProperty = std::is_class_v<T> &&
    std::is_same_v<HeaderProperty<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsCookieProperty = std::is_class_v<T> &&
    std::is_same_v<CookieProperty<typename T::value_type, T::kName>, T>;

template <typename T>
concept IsAnyProperty = IsProperty<T> || IsQueryProperty<T> ||
    IsHeaderProperty<T> || IsCookieProperty<T>;

template <typename T>
concept HasTypeOfBody = requires {
  typename std::decay_t<decltype(T::kTypeOfBody)>;
  std::same_as<std::decay_t<decltype(T::kTypeOfBody)>, const T>;
};
}  // namespace timetable_vsu_backend::utils::convert