#pragma once
#include <Siv3D/String.hpp>
#include <boost/any.hpp>
#include <functional>
#include <unordered_map>

namespace gsl {
  namespace Event {
      class Function {
      public:
        using ArgumentType = std::unordered_map<s3d::String, boost::any>;
        using EventType = std::function<void(const ArgumentType&)>;

      private:
        std::size_t hash_;
        EventType event_;
        bool enable_;

      public:
        Function(const EventType& Event, std::size_t Hash);
        ~Function();
        bool operator==(std::size_t Hash)const;
        bool operator==(const std::type_info& TypeInfo)const;
        bool operator!()const;
        explicit operator bool()const;
        void operator()(const ArgumentType& Argument)const;
        void Disable();
    };
  }
}