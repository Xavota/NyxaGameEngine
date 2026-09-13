#pragma once

#include "macros/nyCompiler.hpp"

#if NY_CPP20
  #include <concepts>
#endif

#include <type_traits>

namespace nyEngineSDK
{
  template<bool _Test, typename T, typename F>
  struct Conditional : std::conditional<_Test, T, F> {};

  template<bool _Test, typename T, typename F>
  using ConditionalT = typename Conditional<_Test, T, F>::type;

  template<class _Callable, class... _Args>
  struct InvokeResult : std::invoke_result<_Callable, _Args...> {};

  template<class _Callable, class... _Args>
  using InvokeResultT = typename InvokeResult<_Callable, _Args...>::type;


  template<typename T1, typename T2>
  struct IsSame : std::is_same<T1, T2> {};

  template<typename T1, typename T2>
  inline constexpr bool IsSameV = IsSame<T1, T2>::value;

  template<typename T1, typename T2>
  struct IsConvertible : std::is_convertible<T1, T2> {};

  template<typename T1, typename T2>
  inline constexpr bool IsConvertibleV = IsConvertible<T1, T2>::value;

  template<class _Callable, class... _Args>
  struct IsNothrowInvocable : std::is_nothrow_invocable<_Callable, _Args...> {};

  template<class _Callable, class... _Args>
  inline constexpr bool IsNothrowInvocableV = IsNothrowInvocable<_Callable, _Args...>::value;

  template<typename T>
  struct IsInteger : std::bool_constant<
    std::is_integral_v<T> &&
    !std::is_same_v<std::remove_cv_t<T>, bool>
  > {};

  template<typename T>
  struct IsSignedInteger : std::bool_constant<
    IsInteger<T>::value&&
    std::is_signed_v<T>
  > {};

  template<typename T>
  struct IsUnsignedInteger : std::bool_constant<
    IsInteger<T>::value&&
    std::is_unsigned_v<T>
  > {};

  template<typename T>
  struct IsFloatingPoint : std::bool_constant<
    std::is_floating_point_v<T>
  > {};

  template<typename T>
  struct IsNumber : std::bool_constant<
    IsInteger<T>::value ||
    IsFloatingPoint<T>::value
  > {};

  template<typename T>
  struct IsSignedNumber : std::bool_constant<
    IsNumber<T>::value&&
    std::is_signed_v<T>
  > {};

  template<typename T>
  inline constexpr bool IsIntegerV = IsInteger<T>::value;

  template<typename T>
  inline constexpr bool IsSignedIntegerV = IsSignedInteger<T>::value;

  template<typename T>
  inline constexpr bool IsUnsignedIntegerV = IsUnsignedInteger<T>::value;

  template<typename T>
  inline constexpr bool IsFloatingPointV = IsFloatingPoint<T>::value;

  template<typename T>
  inline constexpr bool IsNumberV = IsNumber<T>::value;

  template<typename T>
  inline constexpr bool IsSignedNumberV = IsSignedNumber<T>::value;

#if NY_CPP20

  template<typename T>
  concept Integer = IsIntegerV<T>;

  template<typename T>
  concept SignedInteger = IsSignedIntegerV<T>;

  template<typename T>
  concept UnsignedInteger = IsUnsignedIntegerV<T>;

  template<typename T>
  concept FloatingPoint = IsFloatingPointV<T>;

  template<typename T>
  concept Number = IsNumberV<T>;

  template<typename T>
  concept SignedNumber = IsSignedNumberV<T>;

#endif
}