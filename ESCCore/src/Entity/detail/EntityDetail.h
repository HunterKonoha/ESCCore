#pragma once
#include "../../Data/Transform.h"
#include "../../Data/DataBinder.h"
#include "../../Component/Component.h"
#include <unordered_map>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <Siv3D/String.hpp>

namespace gsl {
  namespace detail {
    struct EntityDetail {
      public:
        Transform trans_;
        std::unordered_map<s3d::String, DataBinder> data_;
        std::unordered_map<s3d::String, std::shared_ptr<gsl::Component>> component_;
        s3d::String name_;

      public:
        EntityDetail(const s3d::String& Name, const boost::uuids::uuid& Uuid);
        EntityDetail(EntityDetail&& Obj);
        ~EntityDetail();
    };
  }
}