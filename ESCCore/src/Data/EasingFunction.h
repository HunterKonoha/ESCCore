#pragma once
#include <Siv3D/String.hpp>
#include <functional>

namespace gsl {
  //�C�[�W���O�֐����`����N���X
  class EasingFunction {
    private:
      std::function<double(double)> function_;
      std::function<double(std::function<double(double)>, double)> easing_;

    public:
      /// <summary>
      /// �C�[�W���O�֐����\�z���܂�
      /// </summary>
      /// <param name="Function">�C�[�W���O�֐�</param>
      /// <param name="Easing">�C�[�W���O�̎d���̊֐�</param>
      EasingFunction(std::function<double(double)> Function, std::function<double(std::function<double(double)>, double)> Easing);

      /// <summary>
      /// �f�X�g���N�^
      /// </summary>
      ~EasingFunction();

      /// <summary>
      /// �C�[�W���O�֐����Ăяo���܂�
      /// </summary>
      /// <param name="t">0.0�`1.0�܂ł̏����l</param>
      /// <returns>�{��</returns>
      double operator()(double t)const;

    public:
      /// <summary>
      /// �����񂩂�C�[�W���O�֐����擾���܂�
      /// </summary>
      /// <param name="Str">������</param>
      /// <returns>�C�[�W���O�֐�</returns>
      static std::function<double(double)> ToFunction(const s3d::String& Str);

      /// <summary>
      /// �����񂩂�C�[�W���O�̎d�����擾���܂�
      /// </summary>
      /// <param name="Str">������</param>
      /// <returns>�C�[�W���O�̎d��</returns>
      static std::function<double(std::function<double(double)>, double)> ToEasing(const s3d::String& Str);
  };

  namespace Easing {
    static const EasingFunction LinerInOut(EasingFunction::ToFunction(L"Liner"), EasingFunction::ToEasing(L"InOut"));
    static const EasingFunction QuadInOut(EasingFunction::ToFunction(L"Quad"), EasingFunction::ToEasing(L"InOut"));
  }
}