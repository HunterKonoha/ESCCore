#pragma once
#include <Siv3D/String.hpp>
#include <vector>

namespace Util {
  s3d::String GenerateUUID();
  std::vector<s3d::String> SplitString(const s3d::String& Str, wchar_t Delimiter);
}