#pragma once
#include "../../Util/UuidHash.h"
#include "../Entity.h"
#include "EntityDetail.h"
#include <boost/uuid/uuid.hpp>
#include <unordered_map>

namespace gsl {
  namespace detail {
    class EntityManager {
      private:
        static std::unordered_map<boost::uuids::uuid, EntityDetail, gsl::Util::UuidHash> detail_;
        static EntityDetail root_;

      public:
        static boost::uuids::uuid CreateEntityDetail(const s3d::String& Name);
        static EntityDetail* FindEntityDetail(const boost::uuids::uuid& Uuid);
        static boost::uuids::uuid FindEntityUUIDWithName(const s3d::String& Name);
    };
  }
}