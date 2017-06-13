#include "EntityDetail.h"

gsl::detail::EntityDetail::EntityDetail(const s3d::String & Name, const boost::uuids::uuid & Uuid) :trans_(Uuid), name_(Name) {

}

gsl::detail::EntityDetail::EntityDetail(EntityDetail && Obj) : trans_(std::move(Obj.trans_)), name_(std::move(Obj.name_)), data_(std::move(Obj.data_)) {

}

gsl::detail::EntityDetail::~EntityDetail() {
  this->component_.clear();
  this->data_.clear();
}
