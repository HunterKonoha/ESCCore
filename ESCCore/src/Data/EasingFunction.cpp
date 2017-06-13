#include "EasingFunction.h"
#include <Siv3D/Easing.hpp>

gsl::EasingFunction::EasingFunction(std::function<double(double)> Function, std::function<double(std::function<double(double)>, double)> Easing) :function_(Function), easing_(Easing) {

}

gsl::EasingFunction::~EasingFunction() {

}

double gsl::EasingFunction::operator()(double t) const {
  return this->easing_(this->function_, t);
}

std::function<double(double)> gsl::EasingFunction::ToFunction(const s3d::String & Str) {
  if (Str == L"Sine") {
    return std::bind(s3d::Easing::Sine, std::placeholders::_1);
  }
  else if (Str == L"Cubic") {
    return std::bind(s3d::Easing::Cubic, std::placeholders::_1);
  }
  else if (Str == L"Quint") {
    return std::bind(s3d::Easing::Quint, std::placeholders::_1);
  }
  else if (Str == L"Circ") {
    return std::bind(s3d::Easing::Circ, std::placeholders::_1);
  }
  else if (Str == L"Elastic") {
    return std::bind(s3d::Easing::Elastic, std::placeholders::_1);
  }
  else if (Str == L"Quad") {
    return std::bind(s3d::Easing::Quad, std::placeholders::_1);
  }
  else if (Str == L"Quart") {
    return std::bind(s3d::Easing::Quart, std::placeholders::_1);
  }
  else if (Str == L"Expo") {
    return std::bind(s3d::Easing::Expo, std::placeholders::_1);
  }
  else if (Str == L"Back") {
    return std::bind(s3d::Easing::Back, std::placeholders::_1);
  }
  else if (Str == L"Bounce") {
    return std::bind(s3d::Easing::Bounce, std::placeholders::_1);
  }
  else {
    return std::bind(s3d::Easing::Linear, std::placeholders::_1);
  }
}

std::function<double(std::function<double(double)>, double)> gsl::EasingFunction::ToEasing(const s3d::String & Str) {
  if (Str == L"Out") {
    return std::bind((double(*)(std::function<double(double)>, double))s3d::Easing::EaseOut, std::placeholders::_1, std::placeholders::_2);
  }
  else if (Str == L"InOut") {
    return std::bind((double(*)(std::function<double(double)>, double))s3d::Easing::EaseInOut, std::placeholders::_1, std::placeholders::_2);
  }
  else {
    return std::bind((double(*)(std::function<double(double)>, double))s3d::Easing::EaseIn, std::placeholders::_1, std::placeholders::_2);
  }
}
