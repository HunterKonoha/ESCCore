#pragma once
#include <Siv3D/String.hpp>
#include <functional>

namespace gsl {
  namespace Event {
    class Connection {
      private:
        using SearchFunc = std::function<bool(const s3d::String&, std::size_t)>;
        using UnregisterFunc = std::function<void(const s3d::String&, std::size_t)>;

      private:
        s3d::String eventname_;
        SearchFunc searchreg_;
        UnregisterFunc unreg_;
        std::size_t hash_;

      public:
        Connection(const s3d::String& EventName, std::size_t Hash, const SearchFunc& SearchRegister, const UnregisterFunc& Unregistered);
        ~Connection();
        Connection(Connection&& Obj);
        Connection& operator=(const Connection& Obj) = default;
        bool IsRegistered()const;
        bool IsUnregistered()const;
        void Unregister();
    };
  }
}