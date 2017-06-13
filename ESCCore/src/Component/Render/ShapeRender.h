#pragma once
#include "RenderComponent.h"
#include "Shape/RenderStrategy.h"
#include <Siv3D/Transformer2D.hpp>

namespace gsl {
  namespace Render {
    struct ShapeRenderOption :public RenderOption<ShapeRenderOption> {
      template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type = nullptr>
      ShapeRenderOption& Shape(const T& Value);
      ShapeRenderOption& Shape(const s3d::String& Name);
    };

    template<typename T>
    class ShapeRender :public RenderComponent {
      private:

      public:
        ShapeRender(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority);
        ShapeRender(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority, const ShapeRenderOption& Option);
        ~ShapeRender();
        void Render()override;
    };

    using CircleRender = ShapeRender<Shape::Circle>;
    using RectRender = ShapeRender<Shape::Rect>;
    using TrianlgeRender = ShapeRender<Shape::Triangle>;
    using PolygonRender = ShapeRender<Shape::Polygon>;
  }
}



gsl::Render::ShapeRenderOption & gsl::Render::ShapeRenderOption::Shape(const s3d::String & Name) {
  this->AddValuePair(L"Shape", Name);
  return *this;
}

template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type>
inline gsl::Render::ShapeRenderOption & gsl::Render::ShapeRenderOption::Shape(const T & Value) {
  this->AddTemporaryValue(L"Shape", Value);
  return *this;
}

template<typename T>
gsl::Render::ShapeRender<T>::ShapeRender(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority) :RenderComponent(Name, ID, Priority) {

}

template<typename T>
gsl::Render::ShapeRender<T>::ShapeRender(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority, const ShapeRenderOption & Option) : RenderComponent(Name, ID, Priority, Option) {

}

template<typename T>
gsl::Render::ShapeRender<T>::~ShapeRender() {

}

template<typename T>
void gsl::Render::ShapeRender<T>::Render() {
  T::Render(*this);
}