#pragma once

template<typename T>
inline void gsl::Event::Sender::UnregisterEvent(const s3d::String & Name, T Func) {
  this->UnregisterEvent(Name, typeid(Func));
}