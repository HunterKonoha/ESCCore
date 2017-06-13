#pragma once
#include "../Data/DataBinder.h"
#include "../Event/Sender.h"
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>
#include <boost/uuid/uuid.hpp>
#include <unordered_map>
#include <utility>
#include <Siv3D/Mat3x2.hpp>

namespace gsl {
  struct ComponentOption {
    public:
      std::unordered_map<s3d::String, s3d::String> valuemap_;
      std::vector<std::pair<s3d::String, gsl::DataBinder>> tmpvalue_;

    public:
      ComponentOption& AddValuePair(const s3d::String& Name, const s3d::String& Variable);
      ComponentOption& AddTemporaryValue(const s3d::String& Name, const gsl::DataBinder& Data);
  };

  class Component :public Event::Sender {
    private:
      s3d::String name_;
      boost::uuids::uuid owner_;
      int priority_;
      std::unordered_map<s3d::String, s3d::String> valuemap_;
      std::vector<s3d::String> tmpvalue_;

    public:
      Component(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority);
      Component(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, const ComponentOption& Option);
      virtual ~Component();
      int GetPriority()const;
      const s3d::String& GetName()const;
      const boost::uuids::uuid& GetOwner()const;
      s3d::Optional<DataBinder&> GetData(const s3d::String& Name);
      template<typename T>
      s3d::Optional<T&> GetRawData(const s3d::String& Name);
      const s3d::Mat3x2& GetGlobalMatrix()const;

  };
}

template<typename T>
inline s3d::Optional<T&> gsl::Component::GetRawData(const s3d::String & Name) {
  auto data = this->GetData(Name);
  if (data) {
    return data->Get<T>();
  }
  else {
    return s3d::none;
  }
}