#pragma once
#include "RenderComponent.h"
#include <Siv3D/FontAsset.hpp>
#include <vector>

namespace gsl {
  namespace Render {
    struct TextRenderOption :public RenderOption<TextRenderOption> {
      TextRenderOption& Text(const s3d::String& Name);
      TextRenderOption& Text(const std::vector<s3d::String>& Value);
      TextRenderOption& FontAsset(const s3d::String& Name);
      TextRenderOption& FontAsset(const s3d::FontAsset& Value);
    };

    class TextRender :public RenderComponent{
    private:

    public:
      TextRender(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority);
      TextRender(const s3d::String& Name, const boost::uuids::uuid& ID, int Priority, const TextRenderOption& Option);
      ~TextRender();
      void Render()override;
    };
  }
}