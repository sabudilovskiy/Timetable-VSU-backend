#pragma once
#include <cstddef>
#include <string>
#include <type_traits>
#include <userver/utils/strong_typedef.hpp>
namespace legacy::models
{
//расставляет % с обоих сторон строки, чтобы запросы в постгресе с
//использованием ILIKE работали как поиск подстроки
class SubString{
 public:
  using UnderlyingType = std::string;
  SubString() = default;
  SubString(const SubString&) = default;
  SubString(SubString&&) noexcept = default;
  SubString& operator=(const SubString&) = default;
  SubString& operator=(SubString&&) noexcept = default;
  template <typename... Args> 
  SubString(Args&&... args) noexcept(std::is_nothrow_constructible_v<std::string, Args&&...>) : data_(std::forward<Args>(args)...){}

  template <typename Arg>
  SubString& operator=(Arg&& args) noexcept(std::is_nothrow_assignable_v<std::string, Arg>){
    data_ = std::forward<Arg>(args);
  }

  std::string& GetUnderlying(){
    return data_;
  }
  const std::string& GetUnderlying() const{
    return data_;
  }

  std::size_t size() const{
    return data_.size();
  }
  auto data() const {
    return data_.data();
  }
  auto operator<=>(const SubString&) const= default;

 private:
  std::string data_{};
};
}  // namespace legacy::models
