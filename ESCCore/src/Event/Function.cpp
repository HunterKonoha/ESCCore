#include "Function.h"

gsl::Event::Function::Function(const EventType & Event, std::size_t Hash) :event_(Event), hash_(Hash), enable_(true) {

}

gsl::Event::Function::~Function() {

}

bool gsl::Event::Function::operator==(std::size_t Hash) const {
  return this->hash_ == Hash;
}

bool gsl::Event::Function::operator==(const std::type_info & TypeInfo) const {
  return this->event_.target_type() == TypeInfo;
}

bool gsl::Event::Function::operator!() const {
  return !(this->operator bool());
}

gsl::Event::Function::operator bool() const {
  return this->enable_;
}

void gsl::Event::Function::operator()(const ArgumentType & Argument) const {
  this->event_(Argument);
}

void gsl::Event::Function::Disable() {
  this->enable_ = false;
}
