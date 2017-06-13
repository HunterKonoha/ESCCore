#include "RenderStrategy.h"
#include "../RenderComponent.h"
#include <Siv3D/Circle.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Triangle.hpp>
#include <Siv3D/Polygon.hpp>
#include <Siv3D/Transformer2D.hpp>

void gsl::Render::Shape::Circle::Render(RenderComponent & Com) {
  auto shape = Com.GetRawData<s3d::Circle>(L"Shape");
  if (shape) {
    s3d::Transformer2D trans(Com.CalcTransformMatrix());
    shape->draw(Com.GetRawData<s3d::Color>(L"Color").value_or(s3d::Palette::White));
  }
}

void gsl::Render::Shape::Rect::Render(RenderComponent & Com) {
  auto shape = Com.GetRawData<s3d::Rect>(L"Shape");
  auto pos = Com.GetRawData<s3d::Vec2>(L"Position");
  if (shape) {
    s3d::Transformer2D trans(Com.CalcTransformMatrix());
    shape->draw(Com.GetRawData<s3d::Color>(L"Color").value_or(s3d::Palette::White));
  }
}

void gsl::Render::Shape::Triangle::Render(RenderComponent & Com) {
  auto shape = Com.GetRawData<s3d::Triangle>(L"Shape");
  if (shape) {
    s3d::Transformer2D trans(Com.CalcTransformMatrix());
    shape->draw(Com.GetRawData<s3d::Color>(L"Color").value_or(s3d::Palette::White));
  }
}

void gsl::Render::Shape::Polygon::Render(RenderComponent & Com) {
  auto shape = Com.GetRawData<s3d::Polygon>(L"Shape");
  if (shape) {
    s3d::Transformer2D trans(Com.CalcTransformMatrix());
    shape->draw(Com.GetRawData<s3d::Color>(L"Color").value_or(s3d::Palette::White));
  }
}
