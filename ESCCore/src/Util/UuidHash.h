#pragma once
#include <boost/uuid/uuid.hpp>

namespace gsl {
  namespace Util {
    struct UuidHash {
      public:
        std::size_t operator()(const boost::uuids::uuid& Uuid) const{
          return boost::uuids::hash_value(Uuid);
        }
    };
  }
}