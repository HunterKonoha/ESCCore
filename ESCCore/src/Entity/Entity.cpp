#include "Entity.h"
#include "detail/EntityManager.h"
#include "../Component/Component.h"
#include <boost/range/adaptor/indexed.hpp>

namespace Local {
  inline gsl::detail::EntityDetail* FindEntity(const s3d::Optional<boost::uuids::uuid>& ID) {
    if (ID) {
      return gsl::detail::EntityManager::FindEntityDetail(*ID);
    }
    return nullptr;
  }
}

gsl::Entity::Entity(const boost::uuids::uuid & Uuid) :id_(Uuid) {

}

gsl::Entity::Entity(boost::uuids::uuid && Uuid) : id_(std::move(Uuid)) {

}

gsl::Entity::Entity(const s3d::String & Name) : id_(detail::EntityManager::CreateEntityDetail(Name)) {

}

gsl::Entity::~Entity() {

}

bool gsl::Entity::operator==(const Entity & Obj) const {
  auto entity = Local::FindEntity(this->id_), target = Local::FindEntity(Obj.id_);
  return (entity != nullptr && target != nullptr && *this->id_ == *Obj.id_);
}

s3d::Optional<gsl::DataBinder&> gsl::Entity::GetData(const s3d::String & Name) {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    auto data = entity->data_.find(Name);
    if (data != entity->data_.end()) {
      return data->second;
    }
  }
  return s3d::none;
}

gsl::Entity & gsl::Entity::CreateData(const s3d::String & Name, const DataBinder & Data) {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    entity->data_[Name] = Data;
  }
  return *this;
}

gsl::Entity & gsl::Entity::RemoveData(const s3d::String & Name) {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    entity->data_.erase(Name);
  }
  return *this;
}

gsl::Entity & gsl::Entity::InitTransform(const gsl::TransformInitializer & Init) {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    entity->trans_.SetCenter(Init.center_).SetScale(Init.scale_).SetRotation(Init.rot_);
  }
  return *this;
}

bool gsl::Entity::IsValid() const {
  return Local::FindEntity(this->id_) != nullptr;
}

s3d::Optional<const s3d::String&> gsl::Entity::GetName() const {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    return entity->name_;
  }
  else {
    return s3d::none;
  }
}

s3d::Optional<const boost::uuids::uuid&> gsl::Entity::GetID() const {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    return *this->id_;
  }
  else {
    return s3d::none;
  }
}

std::vector<gsl::Entity> gsl::Entity::GetChild() const {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    return entity->trans_.GetChild();
  }
  return {};
}

std::vector<gsl::Entity> gsl::Entity::GetChildIf(const std::function<bool(const Entity&)>& Pred) const {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    return entity->trans_.GetChildIf(Pred);
  }
  return {};
}

s3d::Optional<gsl::Transform&> gsl::Entity::GetTransform() {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    return entity->trans_;
  }
  return s3d::none;
}

s3d::Optional<const gsl::Transform&> gsl::Entity::GetTransform() const {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    return entity->trans_;
  }
  return s3d::none;
}

gsl::Entity & gsl::Entity::AddChild(Entity & Obj) {
  auto entity = Local::FindEntity(this->id_);
  auto target = Local::FindEntity(Obj.id_);
  if (entity != nullptr&& target != nullptr) {
    entity->trans_.AddChild(*Obj.id_);
  }
  return *this;
}

gsl::Entity & gsl::Entity::RemoveChild(Entity & Obj) {
  return this->RemoveChildIf([&](const Entity& e) {return Obj == e; });
}

gsl::Entity & gsl::Entity::RemoveChildIf(const std::function<bool(const Entity&)>& Pred) {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    entity->trans_.RemoveChildIf([&](const boost::uuids::uuid& Id) {return Pred(gsl::Entity(Id)); });
  }
  return *this;
}

gsl::Entity & gsl::Entity::SetParent(Entity & Obj) {
  auto entity = Local::FindEntity(this->id_);
  auto target = Local::FindEntity(Obj.id_);
  if (entity != nullptr&& target != nullptr) {
    target->trans_.AddChild(*this->id_);
  }
  return *this;
}

gsl::Entity & gsl::Entity::AddComponent(const std::shared_ptr<gsl::Component>& Obj) {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    entity->component_[Obj->GetName()] = Obj;
  }
  return *this;
}

gsl::Entity & gsl::Entity::RemoveComponent(const s3d::String & Name) {
  return this->RemoveComponentIf([&](const auto& Com) {return Com->GetName() == Name; });
}

gsl::Entity & gsl::Entity::RemoveComponentIf(const std::function<bool(const std::shared_ptr<gsl::Component>&)>& Pred) {
  auto entity = Local::FindEntity(this->id_);
  if (entity != nullptr) {
    for (auto it = entity->component_.begin(); it != entity->component_.end();) {
      if (Pred(it->second)) {
        entity->component_.erase(it);
      }
      else {
        ++it;
      }
    }
  }
  return *this;
}

gsl::Entity gsl::Entity::CreateEntity(const s3d::String & Name) {
  return Entity(detail::EntityManager::CreateEntityDetail(Name));
}

gsl::Entity gsl::Entity::FindEntityWithName(const s3d::String & Name) {
  return Entity(detail::EntityManager::FindEntityUUIDWithName(Name));
}
