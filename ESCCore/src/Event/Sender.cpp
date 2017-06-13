#include "Sender.h"
#include "../Util/UuidHash.h"
#include <boost/uuid/random_generator.hpp>
#include <algorithm>

gsl::Event::Sender::Sender() {
}

gsl::Event::Sender::~Sender() {
}

gsl::Event::Connection gsl::Event::Sender::RegisterEvent(const s3d::String & Name, const Function::EventType & Event) {
  std::size_t hash = Util::UuidHash()(boost::uuids::random_generator()());
  this->event_[Name].emplace_back(Event, hash);
  auto searchreg = [this](const s3d::String& EventName, std::size_t Hash) {
    auto it = this->event_.find(EventName);
    if (it != this->event_.end()) {
      auto find = std::find_if(it->second.cbegin(), it->second.cend(), [&Hash](const Function& f) {return f == Hash; });
      if (find != it->second.end()) {
        return true;
      }
    }
    return false;
  };
  auto unreg = [this](const s3d::String& EventName, std::size_t Hash) {
    auto it = this->event_.find(EventName);
    if (it != this->event_.end()) {
      auto find = std::find_if(it->second.begin(), it->second.end(), [&Hash](const Function& f) {return f == Hash; });
      if (find != it->second.end()) {
        find->Disable();
      }
    }
  };
  return Connection(Name, hash, searchreg, unreg);
}

void gsl::Event::Sender::UnregisterEvent(const s3d::String & Name, const std::type_info & TypeInfo) {
  auto it = this->event_.find(Name);
  if (it != this->event_.end()) {
    auto find = std::find_if(it->second.begin(), it->second.end(), [&TypeInfo](const Function& f) {return f == TypeInfo; });
    if (find != it->second.end()) {
      find->Disable();
    }
  }
}

void gsl::Event::Sender::SendEvent(const s3d::String & Name) {
  this->SendEvent(Name, {});
}

void gsl::Event::Sender::SendEvent(const s3d::String & Name, const Function::ArgumentType & Argument) {
  auto it = this->event_.find(Name);
  if (it != this->event_.end()) {
    bool flag = false;
    for (auto&& func : it->second) {
      if (func) {
        func(Argument);
      }
      else {
        flag = true;
      }
    }
    if (flag) {
      it->second.erase(std::remove_if(it->second.begin(), it->second.end(), [](Function& func) {return !func; }), it->second.end());
    }
  }
}
