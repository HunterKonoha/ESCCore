#include "Transform.h"
#include "../Entity/Entity.h"
#include <boost/range/adaptor/indexed.hpp>

gsl::Transform::Transform(const boost::uuids::uuid & Obj) :self_(Obj) {

}

gsl::Transform::Transform(Transform && Obj) {
  this->self_ = std::move(Obj.self_);
  this->center_ = std::move(Obj.center_);
  this->child_ = std::move(Obj.child_);
  this->globalmatrix_ = std::move(Obj.globalmatrix_);
  this->localmatrix_ = std::move(Obj.localmatrix_);
  this->parent_ = std::move(Obj.parent_);
  this->rot_ = std::move(Obj.rot_);
  this->scale_ = std::move(Obj.scale_);
}

gsl::Transform::~Transform() {

}

gsl::Transform & gsl::Transform::SetCenter(const s3d::Vec2 & Center){
  this->center_ = Center;
  this->LocalMatrixUpdate();
  this->GlobalMatrixUpdate();
  return *this;
}

const s3d::Vec2 & gsl::Transform::GetCenter() const {
  return this->center_;
}

gsl::Transform & gsl::Transform::SetScale(const s3d::Vec2 & Scale){
  this->scale_ = Scale;
  this->LocalMatrixUpdate();
  this->GlobalMatrixUpdate();
  return *this;
}

const s3d::Vec2 & gsl::Transform::GetScale() const {
  return this->scale_;
}

gsl::Transform & gsl::Transform::SetRotation(double Angle) {
  this->rot_ = Angle;
  this->LocalMatrixUpdate();
  this->GlobalMatrixUpdate();
  return *this;
}

double gsl::Transform::GetRotation() const {
  return this->rot_;
}

gsl::Transform & gsl::Transform::AddChild(const boost::uuids::uuid & Obj) {
  this->child_.push_back(Obj);
  auto& last = this->child_.back();
  auto& trans = Entity(last).GetTransform();
  trans->parent_ = this->self_;
  trans->LocalMatrixUpdate();
  trans->GlobalMatrixUpdate();
  return *this;
}

gsl::Transform & gsl::Transform::RemoveChild(const boost::uuids::uuid & Obj) {
  return this->RemoveChildIf([&](const boost::uuids::uuid& Id) {return Obj == Id; });
}

gsl::Transform & gsl::Transform::RemoveChildIf(const std::function<bool(const boost::uuids::uuid&)>& Pred) {
  this->child_.erase(std::remove_if(this->child_.begin(), this->child_.end(), Pred), this->child_.end());
  return *this;
}

gsl::Entity gsl::Transform::GetOwner() {
  return gsl::Entity(this->self_);
}

std::vector<gsl::Entity> gsl::Transform::GetChild() {
  return this->GetChildIf([](auto) {return true; });
}

std::vector<gsl::Entity> gsl::Transform::GetChildIf(const std::function<bool(const Entity&)>& Pred) {
  std::vector<Entity> result;
  for (auto&& id : this->child_) {
    Entity entity(id);
    if (entity.IsValid() && Pred(entity)) {
      result.emplace_back(std::move(entity));
    }
  }
  return result;
}

const s3d::Mat3x2 & gsl::Transform::GetLocalMatrix() const{
  return this->localmatrix_;
}

const s3d::Mat3x2 & gsl::Transform::GetGlobalMatrix() const{
  return this->globalmatrix_;
}

void gsl::Transform::GlobalMatrixUpdate() {
  auto trans = Entity(*this->parent_).GetTransform();
  if (this->parent_ && trans) {
    this->globalmatrix_ = trans->globalmatrix_ * this->localmatrix_;
  }
  else {
    this->globalmatrix_ = this->localmatrix_;
  }
}

void gsl::Transform::LocalMatrixUpdate() {
  this->localmatrix_ = s3d::Mat3x2::Rotate(this->rot_, this->center_).translate(this->center_).scale(this->scale_);
}
