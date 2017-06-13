#include "Connection.h"

gsl::Event::Connection::Connection(const s3d::String & EventName, std::size_t Hash, const SearchFunc & SearchRegister, const UnregisterFunc & Unregistered) :eventname_(EventName), hash_(Hash), searchreg_(SearchRegister), unreg_(Unregistered) {

}

gsl::Event::Connection::~Connection() {

}

gsl::Event::Connection::Connection(Connection && Obj) {
  this->eventname_ = std::move(Obj.eventname_);
  this->searchreg_ = std::move(Obj.searchreg_);
  this->unreg_ = std::move(Obj.unreg_);
  this->hash_ = std::move(Obj.hash_);
}

bool gsl::Event::Connection::IsRegistered() const {
  return this->searchreg_(this->eventname_, this->hash_);
}

bool gsl::Event::Connection::IsUnregistered() const {
  return !this->IsRegistered();
}

void gsl::Event::Connection::Unregister() {
  this->unreg_(this->eventname_, this->hash_);
}
