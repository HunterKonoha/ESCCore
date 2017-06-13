#include "VariableUpdate.h"

gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::From(const s3d::String & Name) {
  this->AddValuePair(L"From", Name);
  return *this;
}

gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::To(const s3d::String & Name) {
  this->AddValuePair(L"To", Name);
  return *this;
}

gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::Time(const s3d::Milliseconds & Value) {
  this->AddTemporaryValue(L"Time", Value);
  return *this;
}

gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::Time(const s3d::String & Name) {
  this->AddValuePair(L"Time", Name);
  return *this;
}

gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::Target(const s3d::String & Name) {
  this->AddValuePair(L"Target", Name);
  return *this;
}

gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::Easing(const gsl::EasingFunction & Value) {
  this->AddTemporaryValue(L"Easing", Value);
  return *this;
}

gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::Easing(const s3d::String & Name) {
  this->AddValuePair(L"Easing", Name);
  return *this;
}
