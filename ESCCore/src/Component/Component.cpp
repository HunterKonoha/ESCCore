#include "Component.h"
#include "../Entity/Entity.h"
#include "../Util/Util.h"

gsl::Component::Component(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority) :name_(Name), owner_(Owner), priority_(Priority) {

}

gsl::Component::Component(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, const ComponentOption & Option) : Component(Name, Owner, Priority) {
  this->valuemap_ = Option.valuemap_;
  gsl::Entity self(this->owner_);
  this->tmpvalue_.reserve(Option.tmpvalue_.size());
  for (auto&& value : Option.tmpvalue_) {
    self.CreateData(value.first, value.second);
    this->tmpvalue_.push_back(value.first);
  }
}

gsl::Component::~Component() {
  gsl::Entity self(this->owner_);
  for (auto&& tmp : this->tmpvalue_) {
    self.RemoveData(tmp);
  }
  this->SendEvent(L"onDisposed", { {L"Self", static_cast<Component*>(this)} });
}

int gsl::Component::GetPriority() const {
  return this->priority_;
}

const s3d::String & gsl::Component::GetName() const {
  return this->name_;
}

const boost::uuids::uuid & gsl::Component::GetOwner() const {
  return this->owner_;
}

s3d::Optional<gsl::DataBinder&> gsl::Component::GetData(const s3d::String & Name) {
  auto find = this->valuemap_.find(Name);
  if (find != this->valuemap_.end()) {
    return  gsl::Entity(this->owner_).GetData(find->second);
  }
  else {
    return s3d::none;
  }
}

const s3d::Mat3x2 & gsl::Component::GetGlobalMatrix() const {
  return gsl::Entity(this->owner_).GetTransform()->GetGlobalMatrix();
}

gsl::ComponentOption & gsl::ComponentOption::AddValuePair(const s3d::String & Name, const s3d::String & Variable) {
  this->valuemap_[Name] = Variable;
  return *this;
}

gsl::ComponentOption & gsl::ComponentOption::AddTemporaryValue(const s3d::String& Name, const gsl::DataBinder & Data) {
  auto uuid = Util::GenerateUUID();
  this->tmpvalue_.emplace_back(uuid, Data);
  this->valuemap_[Name] = uuid;
  return *this;
}
