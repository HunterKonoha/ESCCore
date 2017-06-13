#pragma once
#include <Siv3D/String.hpp>
#include <functional>

namespace gsl {
  //イージング関数を定義するクラス
  class EasingFunction {
    private:
      std::function<double(double)> function_;
      std::function<double(std::function<double(double)>, double)> easing_;

    public:
      /// <summary>
      /// イージング関数を構築します
      /// </summary>
      /// <param name="Function">イージング関数</param>
      /// <param name="Easing">イージングの仕方の関数</param>
      EasingFunction(std::function<double(double)> Function, std::function<double(std::function<double(double)>, double)> Easing);

      /// <summary>
      /// デストラクタ
      /// </summary>
      ~EasingFunction();

      /// <summary>
      /// イージング関数を呼び出します
      /// </summary>
      /// <param name="t">0.0～1.0までの小数値</param>
      /// <returns>倍率</returns>
      double operator()(double t)const;

    public:
      /// <summary>
      /// 文字列からイージング関数を取得します
      /// </summary>
      /// <param name="Str">文字列</param>
      /// <returns>イージング関数</returns>
      static std::function<double(double)> ToFunction(const s3d::String& Str);

      /// <summary>
      /// 文字列からイージングの仕方を取得します
      /// </summary>
      /// <param name="Str">文字列</param>
      /// <returns>イージングの仕方</returns>
      static std::function<double(std::function<double(double)>, double)> ToEasing(const s3d::String& Str);
  };

  namespace Easing {
    static const EasingFunction LinerInOut(EasingFunction::ToFunction(L"Liner"), EasingFunction::ToEasing(L"InOut"));
    static const EasingFunction QuadInOut(EasingFunction::ToFunction(L"Quad"), EasingFunction::ToEasing(L"InOut"));
  }
}