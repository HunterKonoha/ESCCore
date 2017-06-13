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
      /// �f�t�H���g�R���X�g���N�^
      /// </summary>
      DataBinder() = default;

      /// <summary>
      /// �l���󂯎���č\�z���܂�
      /// </summary>
      /// <param name="Value">�l</param>
      template<typename T>
      DataBinder(const T& Value);

      /// <summary>
      /// ���[�u�R���X�g���N�^
      /// </summary>
      /// <param name="Obj">���[�u��</param>
      DataBinder(DataBinder&& Obj);

      DataBinder(const DataBinder&);

      /// <summary>
      /// �f�X�g���N�^
      /// </summary>
      ~DataBinder();

      /// <summary>
      /// �l���󂯎���č\�z���܂�
      /// </summary>
      /// <param name="Value">�l</param>
      template<typename T>
      DataBinder& operator=(const T& Value);

      DataBinder& operator=(const DataBinder&) = default;

      /// <summary>
      /// �i�[���Ă���l��T�^�ɕϊ����Ď擾���܂�
      /// </summary>
      /// <returns>�l</returns>
      template<typename T>
      s3d::Optional<T&> Get();

      /// <summary>
      /// �i�[���Ă���l��T�^�ɕϊ����Ď擾���܂�
      /// </summary>
      /// <returns>�l</returns>
      template<typename T>
       s3d::Optional<const T&> Get()const;
  };
}

#include "DataBinder.inl"