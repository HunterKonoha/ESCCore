#pragma once
#include "../Component.h"
#include <Siv3D/Color.hpp>
#include <Siv3D/Vector2D.hpp>

namespace gsl {
  namespace Render {
    template<typename T>
    struct RenderOption :public ComponentOption {
      private:
        T& Cast();

      public:
        T& Color(const s3d::String& Name);
        T& Color(const s3d::Color& Value);
        T& Position(const s3d::String& Name);
        T& Position(const s3d::Vec2& Value);
        T& Rotation(const s3d::String& Name);
        T& Rotation(double Value);
    };

    class RenderComponent :public Component {
      private:

      public:
        RenderComponent(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority);
        RenderComponent(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority, const ComponentOption& Option);
        s3d::Mat3x2 CalcTransformMatrix();
        virtual ~RenderComponent();
        virtual void Render() = 0;
    };
  }
}

template<typename T>
inline T & gsl::Render::RenderOption<T>::Cast() {
  return static_cast<T&>(*this);
}

template<typename T>
inline T & gsl::Render::RenderOption<T>::Color(const s3d::String & Name) {
  this->AddValuePair(L"Color", Name);
  return this->Cast();
}

template<typename T>
inline T & gsl::Render::RenderOption<T>::Color(const s3d::Color & Value) {
  this->AddTemporaryValue(L"Color", Value);
  return this->Cast();
}

template<typename T>
inline T & gsl::Render::RenderOption<T>::Position(const s3d::String & Name) {
  this->AddValuePair(L"Position", Name);
  return this->Cast();
}

template<typename T>
inline T & gsl::Render::RenderOption<T>::Position(const s3d::Vec2 & Value) {
  this->AddTemporaryValue(L"Position", Value);
  return this->Cast();
}

template<typename T>
inline T & gsl::Render::RenderOption<T>::Rotation(const s3d::String & Name) {
  this->AddValuePair(L"Rotation", Name);
  return this->Cast();
}

template<typename T>
inline T & gsl::Render::RenderOption<T>::Rotation(double Value) {
  this->AddTemporaryValue(L"Rotation", Value);
  return this->Cast();
}