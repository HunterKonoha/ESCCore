#pragma once
#include "Component.h"
#include "../Event/Connection.h"
#include "../Event/Function.h"
#include <vector>
#include <functional>
#include <utility>

namespace gsl {
  template<typename T>
  class ComponentManager {
    private:
      static std::vector<std::pair<T*, gsl::Event::Connection>> data_;
      static std::function<bool(const T&, T*)> compare_;

    public:
      ComponentManager();
      ~ComponentManager();
      static void AddData(T& Data);
      static void Apply(const std::function<void(T*)>& Function);
  };
}

template<typename T>
std::vector<std::pair<T*, gsl::Event::Connection>> gsl::ComponentManager<T>::data_;
template<typename T>
std::function<bool(const T&, T*)> gsl::ComponentManager<T>::compare_= [](const T& Obj1, T* Obj2) {return Obj1.GetPriority() > Obj2->GetPriority(); };

template<typename T>
inline gsl::ComponentManager<T>::ComponentManager() {

}

template<typename T>
inline gsl::ComponentManager<T>::~ComponentManager() {

}

template<typename T>
inline void gsl::ComponentManager<T>::AddData(T & Data) {
  auto event = [&](const gsl::Event::Function::ArgumentType& arg) {
    auto any = arg.at(L"Self");
    auto* self = boost::any_cast<gsl::Component*>(arg.at(L"Self"));
    for (auto it = data_.begin(), end = data_.end(); it != end; ++it) {
      if (it->first == self) {
        it->second.Unregister();
        it->first = nullptr;
        break;
      }
    }
  };
  for (auto it = data_.begin(), end = data_.end(); it != end; ++it) {
    if (compare_(*it->first, &Data)) {
      data_.insert(it, std::make_pair(&Data, Data.RegisterEvent(L"onDisposed", event)));
      return;
    }
  }
  data_.emplace_back(std::make_pair(&Data, Data.RegisterEvent(L"onDisposed", event)));
}

template<typename T>
inline void gsl::ComponentManager<T>::Apply(const std::function<void(T*)>& Function) {
  bool flag = false;
  for (auto&& value : data_) {
    if (value.first == nullptr) {
      flag = true;
    }
    else {
      Function(value.first);
    }
  }
  if (flag) {
    data_.erase(std::remove_if(data_.begin(), data_.end(), [](const std::pair<T*, gsl::Event::Connection>& Pair) {return Pair.first == nullptr; }), data_.end());
  };
}
