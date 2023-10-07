#pragma once
#include <chrono>
#include <userver/utils/strong_typedef.hpp>
namespace models
{
//расставляет % с обоих сторон строки, чтобы запросы в постгресе с
//использованием ILIKE работали как поиск подстроки
using SubString =
    userver::utils::StrongTypedef<struct SubStringTag, std::string>;
}  // namespace models
