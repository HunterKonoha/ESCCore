#include "CycleUpdate.h"

gsl::Update::CycleOption & gsl::Update::CycleOption::Time(const s3d::Milliseconds & Value) {
  this->AddTemporaryValue(L"Time", Value);
  return *this;
}

gsl::Update::CycleOption & gsl::Update::CycleOption::Time(const s3d::String & Name) {
  this->AddValuePair(L"Time", Name);
  return *this;
}

gsl::Update::CycleOption & gsl::Update::CycleOption::Repeat(std::size_t Value) {
  this->AddTemporaryValue(L"Repeat", Value);
  return *this;
}

gsl::Update::CycleOption & gsl::Update::CycleOption::Repeat(const s3d::String & Name) {
  this->AddValuePair(L"Repeat", Name);
  return *this;
}

gsl::Update::CycleOption & gsl::Update::CycleOption::Callback(const std::function<void(CycleUpdate&, const s3d::Milliseconds&)>& Func) {
  this->func_ = Func;
  return *this;
}

gsl::Update::CycleUpdate::CycleUpdate(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, bool Register) :UpdateComponent(Name, Owner, Priority, Register) {
  this->Init();
}

gsl::Update::CycleUpdate::CycleUpdate(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, const CycleOption & Option, bool Register) : UpdateComponent(Name, Owner, Priority, Option, Register) {
  this->Init();
  this->callback_.push_back(Option.func_);
}

gsl::Update::CycleUpdate::~CycleUpdate() {

}

void gsl::Update::CycleUpdate::Init() {
  auto update = [&](UpdateComponent& Com, const s3d::Milliseconds& Time) {
    auto repeat = Com.GetRawData<std::size_t>(L"Repeat");
    auto time = Com.GetRawData<s3d::Milliseconds>(L"Time");
    if (time) {
      if (time.value() * (this->call_ + 1) <= Time) {
        for (auto&& f : this->callback_) {
          f(*this, Time);
        }
        ++this->call_;
      }
      if (repeat) {
        if (this->call_ == repeat.value()) {
          return false;
        }
        else {
          return true;
        }
      }
      return true;
    }
    else {
      for (auto&& f : this->callback_) {
        f(*this, Time);
      }
      ++this->call_;
      if (repeat) {
        if (this->call_ == repeat.value()) {
          return false;
        }
        else {
          return true;
        }
      }
      return true;
    }
    return  true;
  };
  this->ReplaceFunction(update);
}
