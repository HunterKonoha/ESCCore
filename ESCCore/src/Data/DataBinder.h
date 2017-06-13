#pragma once
#include "../Util/TypeDef.h"
#include "../Event/Sender.h"
#include <Siv3D/Optional.hpp>
#include <any>
#include <functional>
#include <array>
#include <vector>

namespace gsl {
  struct BinderEvent {
    static const s3d::String onValueChanged;
  };

  class DataBinder: public gsl::Event::Sender {
    private:
      std::any data_;

    public:
      /// <summary>
      /// デフォルトコンストラクタ
      /// </summary>
      DataBinder() = default;

      /// <summary>
      /// 値を受け取って構築します
      /// </summary>
      /// <param name="Value">値</param>
      template<typename T>
      DataBinder(const T& Value);

      /// <summary>
      /// ムーブコンストラクタ
      /// </summary>
      /// <param name="Obj">ムーブ元</param>
      DataBinder(DataBinder&& Obj);

      DataBinder(const DataBinder&);

      /// <summary>
      /// デストラクタ
      /// </summary>
      ~DataBinder();

      /// <summary>
      /// 値を受け取って構築します
      /// </summary>
      /// <param name="Value">値</param>
      template<typename T>
      DataBinder& operator=(const T& Value);

      DataBinder& operator=(const DataBinder&) = default;

      /// <summary>
      /// 格納している値をT型に変換して取得します
      /// </summary>
      /// <returns>値</returns>
      template<typename T>
      s3d::Optional<T&> Get();

      /// <summary>
      /// 格納している値をT型に変換して取得します
      /// </summary>
      /// <returns>値</returns>
      template<typename T>
       s3d::Optional<const T&> Get()const;
  };
}

#include "DataBinder.inl"