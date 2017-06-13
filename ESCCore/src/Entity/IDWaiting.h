#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>
#include <boost/uuid/uuid.hpp>

namespace gsl {
  class IDWaiting {
    private:
      s3d::String names;

    public:
      IDWaiting(const s3d::String& Name);
      ~IDWaiting();
      s3d::Optional<boost::uuids::uuid> operator()()const;
  };
}