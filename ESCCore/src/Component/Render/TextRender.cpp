#include "TextRender.h"
#include <boost/range/adaptor/indexed.hpp>
#include <Siv3D/Transformer2D.hpp>

gsl::Render::TextRenderOption & gsl::Render::TextRenderOption::Text(const s3d::String & Name) {
  this->AddValuePair(L"Text", Name);
  return *this;
}

gsl::Render::TextRenderOption & gsl::Render::TextRenderOption::Text(const std::vector<s3d::String>& Value) {
  this->AddTemporaryValue(L"Text", Value);
  return *this;
}

gsl::Render::TextRenderOption & gsl::Render::TextRenderOption::FontAsset(const s3d::String & Name) {
  this->AddValuePair(L"Font", Name);
  return *this;
}

gsl::Render::TextRenderOption & gsl::Render::TextRenderOption::FontAsset(const s3d::FontAsset & Value) {
  this->AddTemporaryValue(L"Font", Value);
  return *this;
}

gsl::Render::TextRender::TextRender(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority) :RenderComponent(Name, ID, Priority) {

}

gsl::Render::TextRender::TextRender(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority, const TextRenderOption & Option) : RenderComponent(Name, ID, Priority, Option) {

}

gsl::Render::TextRender::~TextRender() {

}

void gsl::Render::TextRender::Render() {
  auto text = this->GetRawData<std::vector<s3d::String>>(L"Text");
  auto font = this->GetRawData<s3d::FontAsset>(L"Font");
  if (text && font) {
    s3d::Transformer2D trans(this->CalcTransformMatrix());
    for (auto&& str : *text | boost::adaptors::indexed(0)) {
      font->draw(str.value(), this->GetRawData<s3d::Vec2>(L"Position").value_or(s3d::Vec2::Zero) + s3d::Vec2(0, str.index() * font->height), this->GetRawData<s3d::Color>(L"Color").value_or(s3d::Palette::White));
    }
  }
}
