#pragma once
#include "RenderComponent.h"
#include <Siv3D/Texture.hpp>
#include <Siv3D/DynamicTexture.hpp>
#include <Siv3D/TextureAsset.hpp>
#include <Siv3D/Transformer2D.hpp>

namespace gsl {
  namespace Render {
    struct ImageRenderOption :public RenderOption<ImageRenderOption>{
      template<typename T, typename std::enable_if<std::is_base_of<s3d::Texture, T>::value, std::nullptr_t>::type = nullptr>
      ImageRenderOption& Texture(const T& Value);
      ImageRenderOption& Texture(const s3d::String& Name);
    };

    template<typename T>
    class ImageRender :public RenderComponent {
      private:

      public:
        ImageRender(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority);
        ImageRender(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority, const ImageRenderOption& Option);
        ~ImageRender();
        void Render()override;
    };

    using TextureRender = ImageRender<s3d::Texture>;
    using DynamicTextureRender = ImageRender<s3d::DynamicTexture>;
    using TextureAssetRender = ImageRender<s3d::TextureAsset>;
  }
}


template<typename T, typename std::enable_if<std::is_base_of<s3d::Texture, T>::value, std::nullptr_t>::type>
inline gsl::Render::ImageRenderOption & gsl::Render::ImageRenderOption::Texture(const T & Value) {
  this->AddTemporaryValue(L"Texture", Value);
  return *this;
}

inline gsl::Render::ImageRenderOption & gsl::Render::ImageRenderOption::Texture(const s3d::String & Name) {
  this->AddValuePair(L"Texture", Name);
  return *this;
}

template<typename T>
inline gsl::Render::ImageRender<T>::ImageRender(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority) :RenderComponent(Name, ID, Priority) {

}

template<typename T>
inline gsl::Render::ImageRender<T>::ImageRender(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority, const ImageRenderOption & Option) : RenderComponent(Name, ID, Priority, Option) {

}

template<typename T>
inline gsl::Render::ImageRender<T>::~ImageRender() {

}

template<typename T>
inline void gsl::Render::ImageRender<T>::Render() {
  auto texture = this->GetRawData<T>(L"Texture");
  if (texture) {
    s3d::Transformer2D trans(this->CalcTransformMatrix());
    texture->draw();
  }
}