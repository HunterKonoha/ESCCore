#pragma once
#include <Siv3D/Optional.hpp>
#include <algorithm>

namespace gsl {
  namespace Algorithm {
    template<template<class ,class> class Type,class Pred,class T,class Alloc>
    s3d::Optional<T&> find_if(Type<T, Alloc>& Containar, Pred&& Func);
  }
}

template<template<class , class> class Type, class Pred, class T, class Alloc>
s3d::Optional<T&> gsl::Algorithm::find_if(Type<T, Alloc>& Containar, Pred&& Func) {
  auto find = std::find_if(Containar.begin(), Containar.end(), Func);
  if (find == Containar.end()) {
    return s3d::none;
  }
  else {
    return *find;
  }
}