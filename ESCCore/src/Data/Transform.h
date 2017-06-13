#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Mat3x2.hpp>
#include <boost/uuid/uuid.hpp>
#include <vector>
#include <optional>
#include <functional>

namespace gsl {
  class Entity;

  struct TransformInitializer {
    s3d::Vec2 center_ = s3d::Vec2::Zero, scale_ = s3d::Vec2::One;
    double rot_ = 0.0;

    TransformInitializer& Center(const s3d::Vec2& Center) {
      this->center_ = Center;
      return *this;
    }

    TransformInitializer& Scale(const s3d::Vec2& Scale) {
      this->scale_ = Scale;
      return *this;
    }

    TransformInitializer& Rotation(double Rot) {
      this->rot_ = Rot;
      return *this;
    }
  };

  class Transform {
    private:
      s3d::Vec2 center_ = s3d::Vec2::Zero, scale_ = s3d::Vec2::One;
      double rot_ = 0.0;
      boost::uuids::uuid self_;
      std::optional<boost::uuids::uuid> parent_;
      std::vector<boost::uuids::uuid> child_;
      s3d::Mat3x2 localmatrix_, globalmatrix_;

    public:
      Transform(const boost::uuids::uuid& Owner);
      Transform(Transform&& Obj);
      ~Transform();
      Transform& SetCenter(const s3d::Vec2& Center);
      const s3d::Vec2& GetCenter()const;
      Transform& SetScale(const s3d::Vec2& Scale);
      const s3d::Vec2& GetScale()const;
      Transform& SetRotation(double Angle);
      double GetRotation()const;
      Transform& AddChild(const boost::uuids::uuid& Obj);
      Transform& RemoveChild(const boost::uuids::uuid& Obj);
      Transform& RemoveChildIf(const std::function<bool(const boost::uuids::uuid&)>& Pred);
      Entity GetOwner();
      std::vector<Entity> GetChild();
      std::vector<Entity> GetChildIf(const std::function<bool(const Entity&)>& Pred);
      const s3d::Mat3x2& GetLocalMatrix()const;
      const s3d::Mat3x2& GetGlobalMatrix()const;

    private:
      void GlobalMatrixUpdate();
      void LocalMatrixUpdate();
  };
}