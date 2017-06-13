#pragma once
#include "UpdateComponent.h"
#include "../../Data/EasingFunction.h"
#include "../../Entity/IDWaiting.h"

namespace gsl {
  namespace Update {
    struct TransformData {
      public:
        s3d::Vec2 center_ = s3d::Vec2::Zero, scale_ = s3d::Vec2::One;
        double rot_ = 0.0;

      public:
        TransformData operator+(const TransformData& Obj)const;
        TransformData operator-(const TransformData& Obj)const;
        TransformData operator*(double Obj)const;
        TransformData& operator=(const TransformData& Obj) = default;
        TransformData& Center(const s3d::Vec2& Value);
        TransformData& Scale(const s3d::Vec2& Value);
        TransformData& Rotation(double Value);
    };

    struct TransformOption :public UpdateOption {
      TransformOption& Target(const IDWaiting& Value);
      TransformOption& Target(const s3d::String& Name);
      TransformOption& From(const TransformData& Value);
      TransformOption& From(const IDWaiting& Value);
      TransformOption& From(const s3d::String& Name);
      TransformOption& To(const TransformData& Value);
      TransformOption& To(const s3d::String& Name);
      TransformOption& Time(const s3d::Milliseconds& Value);
      TransformOption& Time(const s3d::String& Name);
      TransformOption& Easing(const gsl::EasingFunction& Value);
      TransformOption& Easing(const s3d::String& Name);
    };

    class TransformUpdate :public UpdateComponent {
      private:
        s3d::Optional<TransformData> from_ = s3d::none;

      public:
        TransformUpdate(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, bool Register = true);
        TransformUpdate(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, const TransformOption& Option, bool Register = true);
        ~TransformUpdate();

      private:
        void Init();
    };
  }
}