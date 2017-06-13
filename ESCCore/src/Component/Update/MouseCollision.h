#pragma once
#include "UpdateComponent.h"

namespace gsl {
  namespace Update {
    struct MouseCollisionOption :public UpdateOption {

    };

    class MouseCollision :public UpdateComponent {
      private:

      public:
        MouseCollision(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, bool Register = true);
        MouseCollision(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, const MouseCollisionOption& Option, bool Register = true);
        ~MouseCollision();

    };
  }
}