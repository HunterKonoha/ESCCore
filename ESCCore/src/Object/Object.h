#pragma once
#include "../Data/DataBinder.h"
#include "../Data/Transform.h"
#include <unordered_map>
#include <optional>
#include <Siv3D/String.hpp>

namespace gsl {
  class Object {
    private:
      s3d::String name_;
      gsl::Transform trans_;
      std::unordered_map<s3d::String, gsl::DataBinder> data_;

    public:
      Object();
      ~Object();
      gsl::Transform& GetTransform()const;
      gsl::DataBinder& GetData(const s3d::String& Key)const;
      std::optional<gsl::DataBinder&> GetDataOptional(const s3d::String& Key)const;
      Object& AddChild(const s3d::String& Name);
  };
}