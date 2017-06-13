#include "UpdateComponent.h"
#include "../ComponentManager.h"

gsl::Update::UpdateOption & gsl::Update::UpdateOption::Update(const std::function<bool(UpdateComponent&, const s3d::Milliseconds&)>& Func) {
  this->update_ = Func;
  return *this;
}

gsl::Update::UpdateComponent::UpdateComponent(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, bool Register) :Component(Name, Owner, Priority) {
  if (Register) {
    this->RegisterManager();
  }
  this->update_.emplace_back([](auto&, const auto&) {return true; });
}

gsl::Update::UpdateComponent::UpdateComponent(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, const UpdateOption & Option, bool Register) : Component(Name, Owner, Priority, Option) {
  if (Register) {
    this->RegisterManager();
  }
  this->update_.emplace_back([](auto&, const auto&) {return true; });
}

gsl::Update::UpdateComponent::~UpdateComponent() {

}

void gsl::Update::UpdateComponent::Update() {
  if (!this->timer_) {
    this->timer_ = s3d::Stopwatch(true);
  }
  if (!this->update_.empty()) {
    if (!this->update_.back()(*this, this->timer_->elapsed())) {
      this->update_.pop_back();
      if (this->update_.empty()) {
        //自身をマネージャから削除する
        this->timer_ = s3d::none;
      }
    }
  }
}

gsl::Update::UpdateComponent & gsl::Update::UpdateComponent::PushFunction(const std::function<bool(UpdateComponent&, const s3d::Milliseconds&)>& Func) {
  this->update_.push_back(Func);
  return *this;
}

gsl::Update::UpdateComponent & gsl::Update::UpdateComponent::ReplaceFunction(const std::function<bool(UpdateComponent&, const s3d::Milliseconds&)>& Func) {
  if (!this->update_.empty()) {
    this->update_.back() = Func;
  }
  return *this;
}

gsl::Update::UpdateComponent & gsl::Update::UpdateComponent::PopFunction() {
  this->update_.pop_back();
  return *this;
}

void gsl::Update::UpdateComponent::RegisterManager() {
  ComponentManager<UpdateComponent>::AddData(*this);
}
