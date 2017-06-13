#pragma once
#include <Siv3D/String.hpp>
#include <array>
#include <unordered_map>

namespace Util {
  template<typename Type, typename Enum, Enum Value>
  using EnumArray = std::array<Type, static_cast<std::size_t>(Value)>;
  template<typename Type, typename Enum>
  using EnumSizedArray = EnumArray<Type, Enum, Enum::Size>;
  template<typename T>
  using StringKeyMap = std::unordered_map<s3d::String, T>;
}