#include "Util.h"
#include <Siv3D/CharacterSet.hpp>
//#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_serialize.hpp>

s3d::String Util::GenerateUUID() {
  return s3d::CharacterSet::Widen(boost::uuids::to_string(boost::uuids::random_generator()()));
}

std::vector<s3d::String> Util::SplitString(const s3d::String & Str, wchar_t Delimiter) {
  return Str.split(Delimiter);
}
