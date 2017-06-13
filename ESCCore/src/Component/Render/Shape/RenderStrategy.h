#pragma once

namespace gsl {
  namespace Render {
    class RenderComponent;

    namespace Shape {
      struct Circle {
        static void Render(RenderComponent& Com);
      };

      struct Rect {
        static void Render(RenderComponent& Com);
      };

      struct Triangle {
        static void Render(RenderComponent& Com);
      };

      struct Polygon {
        static void Render(RenderComponent& Com);
      };
    }
  }
}