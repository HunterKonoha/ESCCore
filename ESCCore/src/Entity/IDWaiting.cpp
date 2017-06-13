#include "IDWaiting.h"
#include "Entity.h"

gsl::IDWaiting::IDWaiting(const s3d::String & Name) :names(Name) {

}

gsl::IDWaiting::~IDWaiting() {

}

s3d::Optional<boost::uuids::uuid> gsl::IDWaiting::operator()() const {
  auto id = Entity::FindEntityWithName(this->names).GetID();
  if (id) {
    return id.value();
  }
  else {
    return s3d::none;
  }
}
