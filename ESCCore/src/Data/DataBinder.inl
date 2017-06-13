#pragma once

template<typename T>
inline gsl::DataBinder::DataBinder(const T & Value) {
  this->data_ = Value;
}

template<typename T>
inline gsl::DataBinder & gsl::DataBinder::operator=(const T & Value) {
  this->data_ = Value;
  this->SendEvent(BinderEvent::onValueChanged, { {L"Value",*this} });
  return *this;
}

template<typename T>
inline s3d::Optional<T&> gsl::DataBinder::Get() {
  auto* ptr = std::any_cast<T>(&this->data_);
  if (ptr != nullptr) {
    return *ptr;
  }
  else {
    return s3d::none;
  }
}

template<typename T>
inline s3d::Optional<const T&> gsl::DataBinder::Get() const {
  const auto* ptr std::any_cast<T>(&this->data_);
  if (ptr != nullptr) {
    return *ptr;
  }
  else {
    return s3d::none;
  }
}
