#pragma once
#include "../Component.h"
#include <Siv3D/Stopwatch.hpp>
#include <Siv3D/Optional.hpp>
#include <functional>
#include <vector>

namespace gsl {
  namespace Update {
    class UpdateComponent;

    struct UpdateOption :public ComponentOption {
      public:
        std::function<bool(UpdateComponent&, const s3d::Milliseconds&)> update_ = [](auto&, const auto&) {return true; };

      public:
        UpdateOption& Update(const std::function<bool(UpdateComponent&, const s3d::Milliseconds&)>& Func);
    };

    class UpdateComponent :public Component{
      private:
        std::vector<std::function<bool(UpdateComponent&, const s3d::Milliseconds&)>> update_;
        s3d::Optional<s3d::Stopwatch> timer_;

      public:
        UpdateComponent(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, bool Register = true);
        UpdateComponent(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, const UpdateOption& Option, bool Register = true);
        virtual ~UpdateComponent();
        void Update();

      protected:
        UpdateComponent& PushFunction(const std::function<bool(UpdateComponent&, const s3d::Milliseconds&)>& Func);
        UpdateComponent& ReplaceFunction(const std::function<bool(UpdateComponent&, const s3d::Milliseconds&)>& Func);
        UpdateComponent& PopFunction();

      private:
        void RegisterManager();
    };
  }
}