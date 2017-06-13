#include "DataBinder.h"

const s3d::String gsl::BinderEvent::onValueChanged = L"onValueChanged";

gsl::DataBinder::DataBinder(DataBinder && Obj):data_(std::move(Obj.data_)) {

}

gsl::DataBinder::DataBinder(const DataBinder & Obj):data_(Obj.data_) {

}

gsl::DataBinder::~DataBinder() {
}