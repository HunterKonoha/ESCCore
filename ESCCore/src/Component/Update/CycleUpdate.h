#pragma once
#include "UpdateComponent.h"
#include <vector>
#include <functional>

namespace gsl {
  namespace Update {
    class CycleUpdate;

    struct CycleOption :public UpdateOption {
      std::function<void(CycleUpdate&, const s3d::Milliseconds&)> func_ = [](auto&, const auto&) {};

      CycleOption& Time(const s3d::Milliseconds& Value);
      CycleOption& Time(const s3d::String& Name);
      CycleOption& Repeat(std::size_t Value);
      CycleOption& Repeat(const s3d::String& Name);
      CycleOption& Callback(const std::function<void(CycleUpdate&, const s3d::Milliseconds&)>& Func);
    };

    class CycleUpdate :public UpdateComponent {
      private:
        std::vector<std::function<void(CycleUpdate&, const s3d::Milliseconds&)>> callback_;
        std::size_t call_ = 0;

      public:
        CycleUpdate(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, bool Register = true);
        CycleUpdate(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, const CycleOption& Option, bool Register = true);
        ~CycleUpdate();

      private:
        void Init();
    };
  }
}