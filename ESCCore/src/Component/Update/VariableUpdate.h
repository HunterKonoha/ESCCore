#pragma once
#include "UpdateComponent.h"
#include "../../Data/EasingFunction.h"

namespace gsl {
  namespace Update {
    struct VariableUpdateOption :public UpdateOption {
      template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type = nullptr>
      VariableUpdateOption& From(const T& Value);
      VariableUpdateOption& From(const s3d::String& Name);
      template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type = nullptr>
      VariableUpdateOption& To(const T& Value);
      VariableUpdateOption& To(const s3d::String& Name);
      VariableUpdateOption& Time(const s3d::Milliseconds& Value);
      VariableUpdateOption& Time(const s3d::String& Name);
      template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type = nullptr>
      VariableUpdateOption& Target(const T& Value);
      VariableUpdateOption& Target(const s3d::String& Name);
      VariableUpdateOption& Easing(const gsl::EasingFunction& Value);
      VariableUpdateOption& Easing(const s3d::String& Name);
    };

    template<typename T>
    class VariableUpdate :public UpdateComponent {
      private:
        s3d::Optional<T> from_ = s3d::none;

      public:
        VariableUpdate(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, bool Register = true);
        VariableUpdate(const s3d::String& Name, const boost::uuids::uuid& Owner, int Priority, const VariableUpdateOption& Option, bool Register = true);
        ~VariableUpdate();

      private:
        void SetUpdateFunction();
        void SetFrom();
    };
  }
}

template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type>
inline gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::From(const T & Value) {
  this->AddTemporaryValue(L"From", Value);
  return *this;
}

template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type>
inline gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::To(const T & Value) {
  this->AddTemporaryValue(L"To", Value);
  return *this;
}

template<typename T, typename std::enable_if<!std::is_convertible<T, s3d::String>::value, std::nullptr_t>::type>
inline gsl::Update::VariableUpdateOption & gsl::Update::VariableUpdateOption::Target(const T & Value) {
  this->AddTemporaryValue(L"Target", Value);
  return *this;
}

template<typename T>
inline gsl::Update::VariableUpdate<T>::VariableUpdate(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, bool Register) :UpdateComponent(Name, Owner, Priority, Register) {
  this->SetUpdateFunction();
  this->SetFrom();
}

template<typename T>
inline gsl::Update::VariableUpdate<T>::VariableUpdate(const s3d::String & Name, const boost::uuids::uuid & Owner, int Priority, const VariableUpdateOption & Option, bool Register) : UpdateComponent(Name, Owner, Priority, Option, Register) {
  this->SetUpdateFunction();
  this->SetFrom();
}

template<typename T>
inline gsl::Update::VariableUpdate<T>::~VariableUpdate() {

}

template<typename T>
inline void gsl::Update::VariableUpdate<T>::SetUpdateFunction() {
  this->ReplaceFunction([&](UpdateComponent& Com, const s3d::Milliseconds& Time) {
    auto target = Com.GetRawData<T>(L"Target"), to = Com.GetRawData<T>(L"To");
    auto limit = Com.GetRawData<s3d::Milliseconds>(L"Time");
    auto easing = Com.GetRawData<gsl::EasingFunction>(L"Easing");
    if (!target) {
      target = Com.GetRawData<T>(L"From");
    }
    if (target && this->from_ && to && limit) {
      if (limit > Time) {
        auto t = static_cast<double>(Time.count()) / limit->count();
        *target = *this->from_ + (*to - *this->from_) * easing.value_or(gsl::Easing::LinerInOut)(t);
        return true;
      }
      else {
        *target = *to;
        return false;
      }
    }
    else {
      return false;
    }
  });
}

template<typename T>
inline void gsl::Update::VariableUpdate<T>::SetFrom() {
  auto from = this->GetRawData<T>(L"From");
  if (from) {
    this->from_ = from.value();
  }
}
