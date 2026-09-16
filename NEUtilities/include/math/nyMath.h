/******************************************************************************/
/**
 * @file    nyMath.hpp
 * @author  Dalia Castellanos
 * @date    30/08/2026
 * @brief   Defines every basic math function.
 *
 * A collection of every basic arithmetic, geometric and modular functions.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <cmath>

#include "macros/nyMacros.hpp"
#include "macros/nyUtilitiesApi.hpp"

#include "types/nyConcepts.hpp"
#include "types/nyTypes.hpp"

namespace nyEngineSDK
{
  template<typename>
  inline constexpr bool kAlwaysFalse = false;

  class NY_API Math
  {
   public:
    Math() = delete;

    /**************************************************************************/
    /*                                                                        */
    /*                              Trigonometric                             */
    /*                                                                        */
    /**************************************************************************/
    
    /**
     * @brief  The cosine function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the cosine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    cos(const T& _radian) noexcept;
    /**
     * @brief  The cosine function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the cosine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    cosd(const T& _degree) noexcept;
    /**
     * @brief  The sine function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the sine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    sin(const T& _radian) noexcept;
    /**
     * @brief  The sine function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the sine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    sind(const T& _degree) noexcept;
    /**
     * @brief  The tangent function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the tangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    tan(const T& _radian) noexcept;
    /**
     * @brief  The tangent function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the tangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    tand(const T& _degree) noexcept;

    /**
     * @brief  The secant function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the secant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    sec(const T& _radian) noexcept;
    /**
     * @brief  The secant function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the secant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    secd(const T& _degree) noexcept;
    /**
     * @brief  The cosecant function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the cosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    csc(const T& _radian) noexcept;
    /**
     * @brief  The cosecant function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the cosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    cscd(const T& _degree) noexcept;
    /**
     * @brief  The cotangent function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the cotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    cot(const T& _radian) noexcept;
    /**
     * @brief  The cotangent function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the cotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    cotd(const T& _degree) noexcept;

    /**
     * @brief  The arccosine function in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arccosine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    acos(const T& _radian) noexcept;
    /**
     * @brief  The arccosine function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arccosine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    acosd(const T& _degree) noexcept;
    /**
     * @brief  The arcsine function in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arcsine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    asin(const T& _radian) noexcept;
    /**
     * @brief  The arcsine function, in degrees.
     * @param  _degree  The value for the function.
     * @return  The result of the arcsine function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    asind(const T& _degree) noexcept;
    /**
     * @brief  The arctangent function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arctangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    atan(const T& _radian) noexcept;
    /**
     * @brief  The arctangent function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arctangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    atand(const T& _degree) noexcept;
    /**
     * @brief  The arctangent function, for a right triangle with adjacent leg
     *         _x and opposite leg _y.
     * @param  _y  The vY component of the right triangle.
     * @param  _x  The vX component of the right triangle.
     * @return The result of the arctangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    atan2(const T& _y, const T& _x) noexcept;

    /**
     * @brief  The arcsecant function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arcsecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    asec(const T& _radian) noexcept;
    /**
     * @brief  The arcsecant function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arcsecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    asecd(const T& _degree) noexcept;
    /**
     * @brief  The arccosecant function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arccosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    acsc(const T& _radian) noexcept;
    /**
     * @brief  The arccosecant function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arccosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    acscd(const T& _degree) noexcept;
    /**
     * @brief  The arccotangent function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arccotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    acot(const T& _radian) noexcept;
    /**
     * @brief  The arccotangent function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arccotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    acotd(const T& _degree) noexcept;

    /**
     * @brief  Transforms radians to degrees by multiplying with k180_OVER_PI.
     * @param  _radian  The radians to transform.
     * @return The degrees result.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    radToDeg(const T& _radian) noexcept;
    /**
     * @brief  Transforms degrees to radians by multiplying with kPI_OVER_180.
     * @param  _degree  The degree to transform.
     * @return The radians result.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    degToRad(const T& _degree) noexcept;

    /**************************************************************************/
    /*                                                                        */
    /*                               Arithmetic                               */
    /*                                                                        */
    /**************************************************************************/

    /**
     * @brief  The module operation, for floating point numbers.
     * @param  value  The value who's gonna be divided.
     * @param  mod    The value who's gonna divide.
     * @return The result of the module.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    fmod(const T& value, const T& mod) noexcept;

    /**
     * @brief  Get the fractional part of a floating-point number.
     * @param  value  The value who's gonna be divided.
     * @return The fractional part of 'value'.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    frac(const T& value) noexcept;

    /**
     * @brief  The square root operation.
     * @param  _val  The value for the square root.
     * @return The result of the square root.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    sqrt(const T& _val) noexcept;
    /**
     * @brief  The square operation.
     * @param  _val  The value for the square.
     * @return The result of the square.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    sqr(const T& _val) noexcept;
    /**
     * @brief  Returns the power of a value to its exponent.
     * @param  _base   The base of the power.
     * @param  _power  The exponent of the base.
     * @return The result of the power operation.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    pow(const T& _base, const T& _power) noexcept;
    /**
     * @brief  The exponential operation, returns e to the power of the
     *         given value.
     * @param  _power  The exponent of the base.
     * @return The result of the exponential operation.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    exp(const T& _power) noexcept;
    /**
     * @brief  The natural logarithm operation, returns the natural logarithm
     *         of the given value.
     * @param  _val  The value for the logarithm.
     * @return The result of the logarithm operation.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    log(const T& _val) noexcept;
    /**
     * @brief  The logarithm operation, returns the logarithm of the
     *         given value with the specified base.
     * @param  _base  The base of the logarithm.
     * @param  _val  The value for the logarithm.
     * @return The result of the logarithm operation.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    log(const T& _base, const T& _val) noexcept;
    /**
     * @brief  Linearly interpolates between two values based on the given
     *         alpha value.
     * @param  _a      The first value to interpolate from.
     * @param  _b      The second value to interpolate to.
     * @param  _alpha  The interpolation factor, typically in the range [0, 1].
     * @return The interpolated value between _a and _b.
     */
    template<typename T, typename Alpha>
    static NY_FORCE_INLINE NY_NODISCARD T
    lerp(const T& _a, const T& _b, const Alpha& _alpha) noexcept;
    /**
     * @brief  Interpolates between two values based on the given alpha value
     *         and an alpha function.
     * @param  _a      The first value to interpolate from.
     * @param  _b      The second value to interpolate to.
     * @param  _alpha  The interpolation factor, typically in the range [0, 1].
     * @param  _curveFunc  A function that modifies the interpolation factor to
     *                     create a custom interpolation curve.
     * @return The interpolated value between _a and _b.
     */
    template<typename T, typename Alpha, typename Curve>
    static NY_FORCE_INLINE NY_NODISCARD T
    lerp(const T& _a, const T& _b,
         const Alpha&_alpha, Curve&& _curveFunc) noexcept;

    /**
     * @brief  Rounds the given value to the nearest integer.
     * @param  _val  The value to be rounded.
     * @return The value rounded.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    round(const T& _val) noexcept;
    /**
     * @brief  Rounds the given value to the nearest integer below it.
     * @param  _val  The value to be rounded.
     * @return The value rounded.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    floor(const T& _val) noexcept;
    /**
     * @brief  Rounds the given value to the nearest integer above it.
     * @param  _val  The value to be rounded.
     * @return The value rounded.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    ceil(const T& _val) noexcept;
    /**
     * @brief  The absolute value.
     * @param  _val  The value to know its magnitude.
     * @return The absolute value.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    abs(const T& _val) noexcept;
    /**
     * @brief  Returns the sign of the given value as a 1.0f or -1.0f.
     * @param  _val  The value to know its sign.
     * @return The sign value.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    sign(const T& _val) noexcept;
    /**
     * @brief  Composes a floating point value with the magnitude of 'mag' and
     *         the sign of 'sign'.
     * @param  _mag  The value to apply the sign.
     * @param  _sign The value to get the sign.
     * @return The composed value.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    copysign(const T& _mag, const T& _sign) noexcept;
    /**
     * @brief  Returns the maximum value between the first and the second value.
     * @param  _val1  The first value to check.
     * @param  _val2  The second value to check.
     * @return The maximum value between the first and the second value.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    max(const T& _val1, const T& _val2) noexcept;
    /**
     * @brief  Returns the minimum value between the first and the second value.
     * @param  _val1  The first value to check.
     * @param  _val2  The second value to check.
     * @return The minimum value between the first and the second value.
     */
    template<typename T>
    static NY_FORCE_INLINE NY_NODISCARD T
    min(const T& _val1, const T& _val2) noexcept;

    /**
     * @brief  Check if 'value' has contains the 1's bits of 'flag'.
     * @param  _val   The value to check.
     * @param  _flag  The flag to check the 1's bits.
     * @return If the value has the 1's bits of the flag.
     */
    template<typename V, typename F>
    static NY_FORCE_INLINE NY_NODISCARD bool
    hasFlag(const V& _val, const F& _flag) noexcept;


    /***************************************************************************/
    /*                                                                         */
    /*                               Constants                                 */
    /*                                                                         */
    /***************************************************************************/

    /**
     * @brief
     * The approximate value of pi.
     */
    static const f32 kPI;
    static const f64 kPId;
    static const f64L kPIdL;
    /**
     * @brief
     * The approximate value of pi depending on the type.
     */
    template<typename T>
    inline static constexpr T kPi = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kPI;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kPId;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kPIdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kPi only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * Pi divided by 180.
     */
    static const f32 kPI_OVER_180;
    static const f64 kPI_OVER_180d;
    static const f64L kPI_OVER_180dL;
    /**
     * @brief
     * Pi divided by 180 depending on the type.
     */
    template<typename T>
    inline static constexpr T kPiOver180 = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kPI_OVER_180;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kPI_OVER_180d;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kPI_OVER_180dL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kPiOver180 only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * 180 divided by pi.
     */
    static const f32 k180_OVER_PI;
    static const f64 k180_OVER_PId;
    static const f64L k180_OVER_PIdL;
    /**
     * @brief
     * 180 divided by pi depending on the type.
     */
    template<typename T>
    inline static constexpr T k180OverPi = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return k180_OVER_PI;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return k180_OVER_PId;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return k180_OVER_PIdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::k180OverPi only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * Pi times 2.
     */
    static const f32 k2_PI;
    static const f64 k2_PId;
    static const f64L k2_PIdL;
    /**
     * @brief
     * Pi times 2 depending on the type.
     */
    template<typename T>
    inline static constexpr T k2Pi = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return k2_PI;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return k2_PId;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return k2_PIdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::k2Pi only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * Pi over 2.
     */
    static const f32 kPI_OVER_2;
    static const f64 kPI_OVER_2d;
    static const f64L kPI_OVER_2dL;
    /**
     * @brief
     * Pi over 2 depending on the type.
     */
    template<typename T>
    inline static constexpr T kPiOver2 = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kPI_OVER_2;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kPI_OVER_2d;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kPI_OVER_2dL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kPiOver2 only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * Pi over 4.
     */
    static const f32 kPI_OVER_4;
    static const f64 kPI_OVER_4d;
    static const f64L kPI_OVER_4dL;
    /**
     * @brief
     * Pi over 4 depending on the type.
     */
    template<typename T>
    inline static constexpr T kPiOver4 = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kPI_OVER_4;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kPI_OVER_4d;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kPI_OVER_4dL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kPiOver4 only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * The value of e.
     */
    static const f32 kEULER;
    static const f64 kEULERd;
    static const f64L kEULERdL;
    /**
     * @brief
     * The value of e depending on the type.
     */
    template<typename T>
    inline static constexpr T kEuler = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kEULER;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kEULERd;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kEULERdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kEuler only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief A small tolerance for approximate floating point comparisons.
     */
    static const f32 kFLOAT_SMALL;
    static const f64 kFLOAT_SMALLd;
    static const f64L kFLOAT_SMALLdL;
    /**
     * @brief  A small tolerance for approximate floating point comparisons,
     *         depending on the type.
     */
    template<typename T>
    inline static constexpr T kSmallFloat = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kFLOAT_SMALL;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kFLOAT_SMALLd;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kFLOAT_SMALLdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kSmallFloat only supports f32, f64 and f64L."
        );
      }
    }();
    
    /**
     * @brief A very small tolerance for stricter floating point comparisons.
     */
    static const f32 kFLOAT_TINY;
    static const f64 kFLOAT_TINYd;
    static const f64L kFLOAT_TINYdL;
    /**
     * @brief  A tiny tolerance for approximate floating point comparisons,
     *         depending on the type.
     */
    template<typename T>
    inline static constexpr T kTinyFloat = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kFLOAT_TINY;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kFLOAT_TINYd;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kFLOAT_TINYdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kTinyFloat only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * The maximum float possible.
     */
    static const f32 kMAX_FLOAT;
    /**
     * @brief
     * The maximum double possible.
     */
    static const f64 kMAX_FLOATd;
    /**
     * @brief
     * The maximum long double possible.
     */
    static const f64L kMAX_FLOATdL;
    /**
     * @brief  The maximum floating point possible depending on the type.
     */
    template<typename T>
    inline static constexpr T kMaxFloat = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kMAX_FLOAT;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kMAX_FLOATd;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kMAX_FLOATdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kMaxFloat only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * The minimum float possible.
     */
    static const f32 kMIN_FLOAT;
    /**
     * @brief
     * The minimum double possible.
     */
    static const f64 kMIN_FLOATd;
    /**
     * @brief
     * The minimum long double possible.
     */
    static const f64L kMIN_FLOATdL;
    /**
     * @brief  The minimum floating point possible depending on the type.
     */
    template<typename T>
    inline static constexpr T kMinFloat = []()
    {
      if constexpr (IsSameV<T, f32>)
      {
        return kMIN_FLOAT;
      }
      else if constexpr (IsSameV<T, f64>)
      {
        return kMIN_FLOATd;
      }
      else if constexpr (IsSameV<T, f64L>)
      {
        return kMIN_FLOATdL;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kMinFloat only supports f32, f64 and f64L."
        );
      }
    }();

    /**
     * @brief
     * The minimum signed integer of 8 bits possible.
     */
    static const i8 kMIN_INT_8;
    /**
     * @brief
     * The minimum signed integer of 16 bits possible.
     */
    static const i16 kMIN_INT_16;
    /**
     * @brief
     * The minimum signed integer of 32 bits possible.
     */
    static const i32 kMIN_INT_32;
    /**
     * @brief
     * The minimum signed integer of 64 bits possible.
     */
    static const i64 kMIN_INT_64;
    /**
     * @brief  The minimum signed integer possible depending on the type.
     */
    template<typename T>
    inline static constexpr T kMinInt = []()
    {
      if constexpr (IsSameV<T, i8>)
      {
        return kMIN_INT_8;
      }
      else if constexpr (IsSameV<T, i16>)
      {
        return kMIN_INT_16;
      }
      else if constexpr (IsSameV<T, i32>)
      {
        return kMIN_INT_32;
      }
      else if constexpr (IsSameV<T, i64>)
      {
        return kMIN_INT_64;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kMinInt only supports i8, i16, i32 and i64."
        );
      }
    }();

    /**
     * @brief
     * The maximum signed integer of 8 bits possible.
     */
    static const i8 kMAX_INT_8;
    /**
     * @brief
     * The maximum signed integer of 16 bits possible.
     */
    static const i16 kMAX_INT_16;
    /**
     * @brief
     * The maximum signed integer of 32 bits possible.
     */
    static const i32 kMAX_INT_32;
    /**
     * @brief
     * The maximum signed integer of 64 bits possible.
     */
    static const i64 kMAX_INT_64;
    /**
     * @brief  The maximum signed integer possible depending on the type.
     */
    template<typename T>
    inline static constexpr T kMaxInt = []()
    {
      if constexpr (IsSameV<T, i8>)
      {
        return kMAX_INT_8;
      }
      else if constexpr (IsSameV<T, i16>)
      {
        return kMAX_INT_16;
      }
      else if constexpr (IsSameV<T, i32>)
      {
        return kMAX_INT_32;
      }
      else if constexpr (IsSameV<T, i64>)
      {
        return kMAX_INT_64;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kMaxInt only supports i8, i16, i32 and i64."
        );
      }
    }();

    /**
     * @brief
     * The maximum unsigned integer of 8 bits possible.
     */
    static const u8 kMAX_UINT_8;
    /**
     * @brief
     * The maximum unsigned integer of 16 bits possible.
     */
    static const u16 kMAX_UINT_16;
    /**
     * @brief
     * The maximum unsigned integer of 32 bits possible.
     */
    static const u32 kMAX_UINT_32;
    /**
     * @brief
     * The maximum unsigned integer of 64 bits possible.
     */
    static const u64 kMAX_UINT_64;
    /**
     * @brief  The maximum unsigned integer possible depending on the type.
     */
    template<typename T>
    inline static constexpr T kMaxUint = []()
    {
      if constexpr (IsSameV<T, u8>)
      {
        return kMAX_UINT_8;
      }
      else if constexpr (IsSameV<T, u16>)
      {
        return kMAX_UINT_16;
      }
      else if constexpr (IsSameV<T, u32>)
      {
        return kMAX_UINT_32;
      }
      else if constexpr (IsSameV<T, u64>)
      {
        return kMAX_UINT_64;
      }
      else
      {
        NY_STATIC_ASSERT(
          kAlwaysFalse<T>,
          "Math::kMaxUint only supports u8, u16, u32 and u64."
        );
      }
    }();

    /**
     * @brief  A linear interpolation function that returns the input value.
     */
    template<typename T>
    constexpr T linear(T t) noexcept;
    /**
     * @brief  A quadratic easing function that accelerates from zero velocity.
     */
    template<typename T>
    constexpr T easeInQuad(T t) noexcept;
    /**
     * @brief  A quadratic easing function that decelerates to zero velocity.
     */
    template<typename T>
    constexpr T easeOutQuad(T t) noexcept;
    /**
     * @brief  A quadratic easing function that accelerates until halfway, then decelerates.
     */
    template<typename T>
    constexpr T smoothStep(T t) noexcept;
  };

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::cos(const T& _radian) noexcept
  {
    return std::cos(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::cosd(const T& _degree) noexcept
  {
    return cos(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::sin(const T& _radian) noexcept
  {
    return std::sin(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::sind(const T& _degree) noexcept
  {
    return sin(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::tan(const T& _radian) noexcept
  {
    return std::tan(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::tand(const T& _degree) noexcept
  {
    return tan(Math::degToRad(_degree));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::sec(const T& _radian) noexcept
  {
    return (T)1 / Math::cos(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::secd(const T& _degree) noexcept
  {
    return sec(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::csc(const T& _radian) noexcept
  {
    return (T)1 / Math::sin(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::cscd(const T& _degree) noexcept
  {
    return csc(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::cot(const T& _radian) noexcept
  {
    return (T)1 / Math::tan(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::cotd(const T& _degree) noexcept
  {
    return cot(Math::degToRad(_degree));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::acos(const T& _radian) noexcept
  {
    return std::acos(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::acosd(const T& _degree) noexcept
  {
    return acos(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::asin(const T& _radian) noexcept
  {
    return std::asin(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::asind(const T& _degree) noexcept
  {
    return asin(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::atan(const T& _radian) noexcept
  {
    return std::atan(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::atand(const T& _degree) noexcept
  {
    return atan(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::atan2(const T& _y, const T& _x) noexcept
  {
    return std::atan2(_y, _x);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::asec(const T& _radian) noexcept
  {
    return acos((T)1 / _radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::asecd(const T& _degree) noexcept
  {
    return asec(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::acsc(const T& _radian) noexcept
  {
    return asin((T)1 / _radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::acscd(const T& _degree) noexcept
  {
    return acsc(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::acot(const T& _radian) noexcept
  {
    return atan((T)1 / _radian);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::acotd(const T& _degree) noexcept
  {
    return acot(Math::degToRad(_degree));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::radToDeg(const T& _radian) noexcept
  {
    return _radian * k180_OVER_PI;
  }
  template<>
  NY_FORCE_INLINE NY_NODISCARD f32
  Math::radToDeg<f32>(const f32& _radian) noexcept
  {
    return _radian * k180_OVER_PI;
  }
  template<>
  NY_FORCE_INLINE NY_NODISCARD f64
  Math::radToDeg<f64>(const f64& _radian) noexcept
  {
    return _radian * k180_OVER_PId;
  }
  template<>
  NY_FORCE_INLINE NY_NODISCARD f64L
  Math::radToDeg<f64L>(const f64L& _radian) noexcept
  {
    return _radian * k180_OVER_PIdL;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::degToRad(const T& _degree) noexcept
  {
    return _degree * kPI_OVER_180;
  }
  template<>
  NY_FORCE_INLINE NY_NODISCARD f32
  Math::degToRad<f32>(const f32& _degree) noexcept
  {
    return _degree * kPI_OVER_180;
  }
  template<>
  NY_FORCE_INLINE NY_NODISCARD f64
  Math::degToRad<f64>(const f64& _degree) noexcept
  {
    return _degree * kPI_OVER_180d;
  }
  template<>
  NY_FORCE_INLINE NY_NODISCARD f64L
  Math::degToRad<f64L>(const f64L& _degree) noexcept
  {
    return _degree * kPI_OVER_180dL;
  }


  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::fmod(const T& value, const T& mod) noexcept
  {
    return std::fmod(value, mod);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::frac(const T& value) noexcept
  {
    return fmod(value, T(1));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::sqrt(const T& _val) noexcept
  {
    return std::sqrt(_val);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::sqr(const T& _val) noexcept
  {
    return _val * _val;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::pow(const T& _base, const T& _power) noexcept
  {
    return std::pow(_base, _power);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::exp(const T& _power) noexcept
  {
    return std::exp(_power);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::log(const T& _val) noexcept
  {
    return std::log(_val);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::log(const T& _base, const T& _val) noexcept
  {
    return std::log(_val) / std::log(_base);
  }

  template<typename T, typename Alpha>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::lerp(const T& _a, const T& _b, const Alpha& _alpha) noexcept
  {
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Alpha must be a floating-point type."
    );

    return _a + (_b - _a) * _alpha;
  }

  template<typename T, typename Alpha, typename Curve>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::lerp(const T& _a, const T& _b,
             const Alpha& _alpha, Curve&& _curveFunc) noexcept
  {
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Alpha must be a floating-point type."
    );

    NY_STATIC_ASSERT(
      (IsNothrowInvocableV<Curve, Alpha>),
      "Curve must be noexcept."
    );

    using R = InvokeResultT<Curve, Alpha>;

    NY_STATIC_ASSERT(
      (IsConvertibleV<R, Alpha>),
      "Curve must return a value convertible to Alpha."
    );

    return lerp(
      _a, _b,
      static_cast<Alpha>(
        std::forward<Curve>(_curveFunc)(_alpha)
      )
    );
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::round(const T& _val) noexcept
  {
    return std::round(_val);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::floor(const T& _val) noexcept
  {
    return std::floor(_val);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::ceil(const T& _val) noexcept
  {
    return std::ceil(_val);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::abs(const T& _val) noexcept
  {
    return std::abs(_val);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::sign(const T& _val) noexcept
  {
    return _val >= T(0) ? T(1) : T(-1);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::copysign(const T& _mag, const T& _sign) noexcept
  {
    return abs(_mag) * sign(_sign);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::max(const T& _val1, const T& _val2) noexcept
  {
    return _val1 > _val2 ? _val1 : _val2;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Math::min(const T& _val1, const T& _val2) noexcept
  {
    return _val1 < _val2 ? _val1 : _val2;
  }

  template<typename V, typename F>
  NY_FORCE_INLINE NY_NODISCARD bool
  Math::hasFlag(const V& _val, const F& _flag) noexcept
  {
    return (_val & _flag) == _flag;
  }


  template<typename T>
  inline constexpr T Math::linear(T t) noexcept
  {
    return t;
  }
  template<typename T>
  inline constexpr T Math::easeInQuad(T t) noexcept
  {
    T result = t * t;
    return result;
  }
  template<typename T>
  inline constexpr T Math::easeOutQuad(T t) noexcept
  {
    T result = t * (T(2) - t);
    return result;
  }
  template<typename T>
  inline constexpr T Math::smoothStep(T t) noexcept
  {
    T result = t * t * (T(3) - T(2) * t);
    return result;
  }
}