#pragma once
#include "../Data/DataBinder.h"
#include "../Data/Transform.h"
#include <boost/uuid/uuid.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>
#include <functional>
#include <memory>

namespace gsl {
  class Component;

  class Entity {
    private:
      s3d::Optional<boost::uuids::uuid> id_;

    public:
      Entity() = default;
      Entity(const boost::uuids::uuid& Uuid);
      Entity(boost::uuids::uuid&& Uuid);
      Entity(const s3d::String& Name);
      ~Entity();
      bool operator==(const Entity& Obj)const;
      s3d::Optional<DataBinder&> GetData(const s3d::String& Name);
      template<typename T>
      s3d::Optional<T&> GetRawData(const s3d::String& Name);
      Entity& CreateData(const s3d::String& Name, const DataBinder& Data);
      Entity& RemoveData(const s3d::String& Name);
      Entity& InitTransform(const gsl::TransformInitializer& Init);
      bool IsValid()const;
      s3d::Optional<const s3d::String&> GetName()const;
      s3d::Optional<const boost::uuids::uuid&> GetID()const;
      std::vector<Entity> GetChild()const;
      std::vector<Entity> GetChildIf(const std::function<bool(const Entity&)>& Pred)const;
      s3d::Optional<gsl::Transform&> GetTransform();
      s3d::Optional<const gsl::Transform&> GetTransform()const;
      Entity& AddChild(Entity& Obj);
      Entity& RemoveChild(Entity& Obj);
      Entity& RemoveChildIf(const std::function<bool(const Entity&)>& Pred);
      Entity& SetParent(Entity& Obj);
      Entity& AddComponent(const std::shared_ptr<gsl::Component>& Obj);
      template<typename T,typename ...Arg>
      Entity& AddComponent(const s3d::String& Name, int Priotity, Arg&... arg);
      Entity& RemoveComponent(const s3d::String& Name);
      Entity& RemoveComponentIf(const std::function<bool(const std::shared_ptr<gsl::Component>&)>& Pred);

    public:
      static Entity CreateEntity(const s3d::String& Name);
      static Entity FindEntityWithName(const s3d::String& Name);
  };
}

template<typename T>
inline s3d::Optional<T&> gsl::Entity::GetRawData(const s3d::String & Name) {
  auto data = this->GetData(Name);
  if (data) {
    return data->Get<T>();
  }
  return s3d::none;
}

template<typename T, typename ...Arg>
inline gsl::Entity & gsl::Entity::AddComponent(const s3d::String & Name, int Priotity, Arg & ...arg) {
  this->AddComponent(std::shared_ptr<gsl::Component>(new T(Name, *this->id_, Priotity, arg...)));
  return *this;
}
