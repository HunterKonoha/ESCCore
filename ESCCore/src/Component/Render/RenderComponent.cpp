#include "RenderComponent.h"
#include "../ComponentManager.h"

gsl::Render::RenderComponent::RenderComponent(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority) :Component(Name, ID, Priority) {
  ComponentManager<RenderComponent>::AddData(*this);
}

gsl::Render::RenderComponent::RenderComponent(const s3d::String & Name, const boost::uuids::uuid & ID, int Priority, const ComponentOption & Option) : Component(Name, ID, Priority, Option) {
  ComponentManager<RenderComponent>::AddData(*this);
}

s3d::Mat3x2 gsl::Render::RenderComponent::CalcTransformMatrix() {
  return this->GetGlobalMatrix()*s3d::Mat3x2::Rotate(this->GetRawData<double>(L"Rotation").value_or(0.0)).translate(this->GetRawData<s3d::Vec2>(L"Position").value_or(s3d::Vec2::Zero));
}

gsl::Render::RenderComponent::~RenderComponent() {

}
