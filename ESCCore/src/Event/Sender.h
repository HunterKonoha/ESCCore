#pragma once
#include <Siv3D/String.hpp>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include "Connection.h"
#include "Function.h"

namespace gsl {
  namespace Event {
    class Sender {
      private:
        std::unordered_map<s3d::String, std::vector<Function>> event_;

      public:
        Sender();
        virtual ~Sender();
        Connection RegisterEvent(const s3d::String& Name, const Function::EventType& Event);
        template<typename T>
        void UnregisterEvent(const s3d::String& Name, T Func);
        void UnregisterEvent(const s3d::String& Name, const std::type_info& TypeInfo);
        void SendEvent(const s3d::String& Name);
        void SendEvent(const s3d::String& Name, const Function::ArgumentType& Argument);
    };
  }
}

#include "Sender.inl"