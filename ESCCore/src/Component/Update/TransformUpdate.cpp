#include "TransformUpdate.h"
#include "../../Entity/Entity.h"

gsl::Update::TransformUpdate::TransformUpdate(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, bool Register) :UpdateComponent(Name, Owner, Priority, Register) {
  this->Init();
}

gsl::Update::TransformUpdate::TransformUpdate(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, const TransformOption & Option, bool Register) : UpdateComponent(Name, Owner, Priority, Option, Register) {
  this->Init();
}

gsl::Update::TransformUpdate::~TransformUpdate() {
}

void gsl::Update::TransformUpdate::Init() {
  auto from_data = this->GetRawData<TransformData>(L"From");
  if (from_data) {
    this->from_.emplace(TransformData().Center(from_data->center_).Rotation(from_data->rot_).Scale(from_data->scale_));
  }
  else {
    auto from_uuid = this->GetRawData<IDWaiting>(L"From");
    if (from_uuid && from_uuid.value()()) {
      auto trans = Entity(from_uuid.value()().value()).GetTransform();
      if (trans) {
        this->from_.emplace(TransformData().Center(trans->GetCenter()).Rotation(trans->GetRotation()).Scale(trans->GetScale()));
      }
    }
  }
  auto update = [&](UpdateComponent& Com, const s3d::Milliseconds& Time) {
    auto limit = Com.GetRawData<s3d::Milliseconds>(L"Time");
    auto target = Com.GetRawData<IDWaiting>(L"Target");
    auto to = Com.GetRawData<TransformData>(L"To");
    auto easing = Com.GetRawData<EasingFunction>(L"Easing");
    if (!target) {
      target = Com.GetRawData<IDWaiting>(L"From");
    }
    if (this->from_ && to && target && target.value()() && limit && easing) {
      auto trans = Entity(*target.value()()).GetTransform();
      if (trans) {
        if (*limit > Time) {
          double t = easing.value()(static_cast<double>(Time.count()) / limit->count());
          auto calc = this->from_.value() + (*to - this->from_.value()) * t;
          trans->SetCenter(calc.center_).SetRotation(calc.rot_).SetScale(calc.scale_);
          return true;
        }
        else {
          trans->SetCenter(to->center_).SetRotation(to->rot_).SetScale(to->scale_);
          return false;
        }
      }
    }
    return true;
  };
  this->ReplaceFunction(update);
}

gsl::Update::TransformOption & gsl::Update::TransformOption::Target(const IDWaiting & Value) {
  this->AddTemporaryValue(L"Target", Value);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::Target(const s3d::String & Name) {
  this->AddValuePair(L"Target", Name);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::From(const TransformData & Value) {
  this->AddTemporaryValue(L"From", Value);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::From(const IDWaiting & Value) {
  this->AddTemporaryValue(L"From", Value);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::From(const s3d::String & Name) {
  this->AddValuePair(L"From", Name);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::To(const TransformData & Value) {
  this->AddTemporaryValue(L"To", Value);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::To(const s3d::String & Name) {
  this->AddValuePair(L"To", Name);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::Time(const s3d::Milliseconds & Value) {
  this->AddTemporaryValue(L"Time", Value);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::Time(const s3d::String & Name) {
  this->AddValuePair(L"Time", Name);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::Easing(const gsl::EasingFunction & Value) {
  this->AddTemporaryValue(L"Easing", Value);
  return *this;
}

gsl::Update::TransformOption & gsl::Update::TransformOption::Easing(const s3d::String & Name) {
  this->AddValuePair(L"Easing", Name);
  return *this;
}

gsl::Update::TransformData gsl::Update::TransformData::operator+(const TransformData & Obj)const {
  return TransformData().Center(this->center_ + Obj.center_).Rotation(this->rot_ + Obj.rot_).Scale(this->scale_ + Obj.scale_);
}

gsl::Update::TransformData gsl::Update::TransformData::operator-(const TransformData & Obj)const {
  return TransformData().Center(this->center_ - Obj.center_).Rotation(this->rot_ - Obj.rot_).Scale(this->scale_ - Obj.scale_);
}

gsl::Update::TransformData gsl::Update::TransformData::operator*(double Obj)const {
  return TransformData().Center(this->center_ * Obj).Rotation(this->rot_ * Obj).Scale(this->scale_ * Obj);
}

gsl::Update::TransformData & gsl::Update::TransformData::Center(const s3d::Vec2 & Value) {
  this->center_ = Value;
  return *this;
}

gsl::Update::TransformData & gsl::Update::TransformData::Scale(const s3d::Vec2 & Value) {
  this->scale_ = Value;
  return *this;
}

gsl::Update::TransformData & gsl::Update::TransformData::Rotation(double Value) {
  this->rot_ = Value;
  return *this;
}
