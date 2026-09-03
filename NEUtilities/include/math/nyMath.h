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
#include "types/nyTypes.hpp"

namespace nyEngineSDK
{
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
    static NY_FORCE_INLINE T
    cos(const T& _radian) noexcept;
    /**
     * @brief  The cosine function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the cosine function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    cosd(const T& _degree) noexcept;
    /**
     * @brief  The sine function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the sine function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    sin(const T& _radian) noexcept;
    /**
     * @brief  The sine function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the sine function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    sind(const T& _degree) noexcept;
    /**
     * @brief  The tangent function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the tangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    tan(const T& _radian) noexcept;
    /**
     * @brief  The tangent function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the tangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    tand(const T& _degree) noexcept;

    /**
     * @brief  The secant function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the secant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    sec(const T& _radian) noexcept;
    /**
     * @brief  The secant function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the secant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    secd(const T& _degree) noexcept;
    /**
     * @brief  The cosecant function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the cosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    csc(const T& _radian) noexcept;
    /**
     * @brief  The cosecant function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the cosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    cscd(const T& _degree) noexcept;
    /**
     * @brief  The cotangent function in radians.
     * @param  _radian  The angle for the function in radians.
     * @return The result of the cotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    cot(const T& _radian) noexcept;
    /**
     * @brief  The cotangent function in degrees.
     * @param  _degree  The angle for the function in degrees.
     * @return The result of the cotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    cotd(const T& _degree) noexcept;

    /**
     * @brief  The arccosine function in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arccosine function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    acos(const T& _radian) noexcept;
    /**
     * @brief  The arccosine function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arccosine function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    acosd(const T& _degree) noexcept;
    /**
     * @brief  The arcsine function in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arcsine function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    asin(const T& _radian) noexcept;
    /**
     * @brief  The arcsine function, in degrees.
     * @param  _degree  The value for the function.
     * @return  The result of the arcsine function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    asind(const T& _degree) noexcept;
    /**
     * @brief  The arctangent function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arctangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    atan(const T& _radian) noexcept;
    /**
     * @brief  The arctangent function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arctangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    atand(const T& _degree) noexcept;
    /**
     * @brief  The arctangent function, for a right triangle with adjacent leg
     *         _x and opposite leg _y.
     * @param  _y  The vY component of the right triangle.
     * @param  _x  The vX component of the right triangle.
     * @return The result of the arctangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    atan2(const T& _y, const T& _x) noexcept;

    /**
     * @brief  The arcsecant function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arcsecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    asec(const T& _radian) noexcept;
    /**
     * @brief  The arcsecant function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arcsecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    asecd(const T& _degree) noexcept;
    /**
     * @brief  The arccosecant function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arccosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    acsc(const T& _radian) noexcept;
    /**
     * @brief  The arccosecant function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arccosecant function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    acscd(const T& _degree) noexcept;
    /**
     * @brief  The arccotangent function, in radians.
     * @param  _radian  The value for the function.
     * @return The result of the arccotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    acot(const T& _radian) noexcept;
    /**
     * @brief  The arccotangent function, in degrees.
     * @param  _degree  The value for the function.
     * @return The result of the arccotangent function.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    acotd(const T& _degree) noexcept;

    /**
     * @brief  Transforms radians to degrees by multiplying with k180_OVER_PI.
     * @param  _radian  The radians to transform.
     * @return The degrees result.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    radToDeg(const T& _radian) noexcept;
    /**
     * @brief  Transforms degrees to radians by multiplying with kPI_OVER_180.
     * @param  _degree  The degree to transform.
     * @return The radians result.
     */
    template<typename T>
    static NY_FORCE_INLINE T
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
    static NY_FORCE_INLINE T
    fmod(const T& value, const T& mod) noexcept;

    /**
     * @brief  Get the fractional part of a floating-point number.
     * @param  value  The value who's gonna be divided.
     * @return The fractional part of 'value'.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    frac(const T& value) noexcept;

    /**
     * @brief  The square root operation.
     * @param  _val  The value for the square root.
     * @return The result of the square root.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    sqrt(const T& _val) noexcept;
    /**
     * @brief  The square operation.
     * @param  _val  The value for the square.
     * @return The result of the square.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    sqr(const T& _val) noexcept;
    /**
     * @brief  Returns the power of a value to its exponent.
     * @param  _base   The base of the power.
     * @param  _power  The exponent of the base.
     * @return The result of the power operation.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    pow(const T& _base, const T& _power) noexcept;
    /**
     * @brief  The exponential operation, returns e to the power of the given value.
     * @param  _power  The exponent of the base.
     * @return The result of the exponential operation.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    exp(const T& _power) noexcept;

    /**
     * @brief  Rounds the given value to the nearest integer.
     * @param  _val  The value to be rounded.
     * @return The value rounded.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    round(const T& _val) noexcept;
    /**
     * @brief  Rounds the given value to the nearest integer below it.
     * @param  _val  The value to be rounded.
     * @return The value rounded.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    floor(const T& _val) noexcept;
    /**
     * @brief  Rounds the given value to the nearest integer above it.
     * @param  _val  The value to be rounded.
     * @return The value rounded.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    ceil(const T& _val) noexcept;
    /**
     * @brief  The absolute value.
     * @param  _val  The value to know its magnitude.
     * @return The absolute value.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    abs(const T& _val) noexcept;
    /**
     * @brief  Returns the sign of the given value as a 1.0f or -1.0f.
     * @param  _val  The value to know its sign.
     * @return The sign value.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    sign(const T& _val) noexcept;
    /**
     * @brief  Composes a floating point value with the magnitude of 'mag' and
     *         the sign of 'sign'.
     * @param  _mag  The value to apply the sign.
     * @param  _sign The value to get the sign.
     * @return The composed value.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    copysign(const T& _mag, const T& _sign) noexcept;
    /**
     * @brief  Returns the maximum value between the first and the second value.
     * @param  _val1  The first value to check.
     * @param  _val2  The second value to check.
     * @return The maximum value between the first and the second value.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    max(const T& _val1, const T& _val2) noexcept;
    /**
     * @brief  Returns the minimum value between the first and the second value.
     * @param  _val1  The first value to check.
     * @param  _val2  The second value to check.
     * @return The minimum value between the first and the second value.
     */
    template<typename T>
    static NY_FORCE_INLINE T
    min(const T& _val1, const T& _val2) noexcept;

    /**
     * @brief  Check if 'value' has contains the 1's bits of 'flag'.
     * @param  _val   The value to check.
     * @param  _flag  The flag to check the 1's bits.
     * @return If the value has the 1's bits of the flag.
     */
    template<typename V, typename F>
    static NY_FORCE_INLINE bool
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
     * Pi divided by 180.
     */
    static const f32 kPI_OVER_180;
    static const f64 kPI_OVER_180d;
    static const f64L kPI_OVER_180dL;
    /**
     * @brief
     * 180 divided by pi.
     */
    static const f32 k180_OVER_PI;
    static const f64 k180_OVER_PId;
    static const f64L k180_OVER_PIdL;
    /**
     * @brief
     * Pi times 2.
     */
    static const f32 k2_PI;
    static const f64 k2_PId;
    static const f64L k2_PIdL;
    /**
     * @brief
     * Pi over 2.
     */
    static const f32 kPI_OVER_2;
    static const f64 kPI_OVER_2d;
    static const f64L kPI_OVER_2dL;
    /**
     * @brief
     * Pi over 4.
     */
    static const f32 kPI_OVER_4;
    static const f64 kPI_OVER_4d;
    static const f64L kPI_OVER_4dL;
    /**
     * @brief
     * The value of e.
     */
    static const f32 kEuler;
    static const f64 kEulerd;
    static const f64L kEulerdL;

    /**
     * @brief A small tolerance for approximate floating point comparisons.
     */
    static const f32 kFLOAT_SMALL;
    /**
     * @brief A very small tolerance for stricter floating point comparisons.
     */
    static const f32 kFLOAT_TINY;
    /**
     * @brief A small tolerance for approximate floating point comparisons.
     */
    static const f64 kFLOAT_SMALLd;
    /**
     * @brief A very small tolerance for stricter floating point comparisons.
     */
    static const f64 kFLOAT_TINYd;
    /**
     * @brief A small tolerance for approximate floating point comparisons.
     */
    static const f64L kFLOAT_SMALLdL;
    /**
     * @brief A very small tolerance for stricter floating point comparisons.
     */
    static const f64L kFLOAT_TINYdL;

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
     * @brief
     * The minimum integer of 8 bits possible.
     */
    static const i8 kMIN_INT_8;
    /**
     * @brief
     * The minimum integer of 16 bits possible.
     */
    static const i16 kMIN_INT_16;
    /**
     * @brief
     * The minimum integer of 32 bits possible.
     */
    static const i32 kMIN_INT_32;
    /**
     * @brief
     * The minimum integer of 64 bits possible.
     */
    static const i64 kMIN_INT_64;

    /**
     * @brief
     * The maximum integer of 8 bits possible.
     */
    static const i8 kMAX_INT_8;
    /**
     * @brief
     * The maximum integer of 16 bits possible.
     */
    static const i16 kMAX_INT_16;
    /**
     * @brief
     * The maximum integer of 32 bits possible.
     */
    static const i32 kMAX_INT_32;
    /**
     * @brief
     * The maximum integer of 64 bits possible.
     */
    static const i64 kMAX_INT_64;

    /**
     * @brief
     * The maximum integer of 8 bits possible.
     */
    static const u8 kMAX_UINT_8;
    /**
     * @brief
     * The maximum integer of 16 bits possible.
     */
    static const u16 kMAX_UINT_16;
    /**
     * @brief
     * The maximum integer of 32 bits possible.
     */
    static const u32 kMAX_UINT_32;
    /**
     * @brief
     * The maximum integer of 64 bits possible.
     */
    static const u64 kMAX_UINT_64;
  };

  template<typename T>
  NY_FORCE_INLINE T
  Math::cos(const T& _radian) noexcept
  {
    return std::cos(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::cosd(const T& _degree) noexcept
  {
    return cos(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::sin(const T& _radian) noexcept
  {
    return std::sin(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::sind(const T& _degree) noexcept
  {
    return sin(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::tan(const T& _radian) noexcept
  {
    return std::tan(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::tand(const T& _degree) noexcept
  {
    return tan(Math::degToRad(_degree));
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::sec(const T& _radian) noexcept
  {
    return (T)1 / Math::cos(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::secd(const T& _degree) noexcept
  {
    return sec(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::csc(const T& _radian) noexcept
  {
    return (T)1 / Math::sin(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::cscd(const T& _degree) noexcept
  {
    return csc(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::cot(const T& _radian) noexcept
  {
    return (T)1 / Math::tan(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::cotd(const T& _degree) noexcept
  {
    return cot(Math::degToRad(_degree));
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::acos(const T& _radian) noexcept
  {
    return std::acos(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::acosd(const T& _degree) noexcept
  {
    return acos(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::asin(const T& _radian) noexcept
  {
    return std::asin(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::asind(const T& _degree) noexcept
  {
    return asin(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::atan(const T& _radian) noexcept
  {
    return std::atan(_radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::atand(const T& _degree) noexcept
  {
    return atan(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::atan2(const T& _y, const T& _x) noexcept
  {
    return std::atan2(_y, _x);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::asec(const T& _radian) noexcept
  {
    return acos((T)1 / _radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::asecd(const T& _degree) noexcept
  {
    return asec(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::acsc(const T& _radian) noexcept
  {
    return asin((T)1 / _radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::acscd(const T& _degree) noexcept
  {
    return acsc(Math::degToRad(_degree));
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::acot(const T& _radian) noexcept
  {
    return atan((T)1 / _radian);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::acotd(const T& _degree) noexcept
  {
    return acot(Math::degToRad(_degree));
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::radToDeg(const T& _radian) noexcept
  {
    return _radian * k180_OVER_PI;
  }
  template<>
  NY_FORCE_INLINE f32
  Math::radToDeg<f32>(const f32& _radian) noexcept
  {
    return _radian * k180_OVER_PI;
  }
  template<>
  NY_FORCE_INLINE f64
  Math::radToDeg<f64>(const f64& _radian) noexcept
  {
    return _radian * k180_OVER_PId;
  }
  template<>
  NY_FORCE_INLINE f64L
  Math::radToDeg<f64L>(const f64L& _radian) noexcept
  {
    return _radian * k180_OVER_PIdL;
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::degToRad(const T& _degree) noexcept
  {
    return _degree * kPI_OVER_180;
  }
  template<>
  NY_FORCE_INLINE f32
  Math::degToRad<f32>(const f32& _degree) noexcept
  {
    return _degree * kPI_OVER_180;
  }
  template<>
  NY_FORCE_INLINE f64
  Math::degToRad<f64>(const f64& _degree) noexcept
  {
    return _degree * kPI_OVER_180d;
  }
  template<>
  NY_FORCE_INLINE f64L
  Math::degToRad<f64L>(const f64L& _degree) noexcept
  {
    return _degree * kPI_OVER_180dL;
  }


  template<typename T>
  NY_FORCE_INLINE T
  Math::fmod(const T& value, const T& mod) noexcept
  {
    return std::fmod(value, mod);
  }
  template<typename T>
  NY_FORCE_INLINE T
  Math::frac(const T& value) noexcept
  {
    return fmod(value, T(1));
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::sqrt(const T& _val) noexcept
  {
    return std::sqrt(_val);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::sqr(const T& _val) noexcept
  {
    return _val * _val;
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::pow(const T& _base, const T& _power) noexcept
  {
    return std::pow(_base, _power);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::exp(const T& _power) noexcept
  {
    return std::exp(_power);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::round(const T& _val) noexcept
  {
    return std::round(_val);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::floor(const T& _val) noexcept
  {
    return std::floor(_val);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::ceil(const T& _val) noexcept
  {
    return std::ceil(_val);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::abs(const T& _val) noexcept
  {
    return std::abs(_val);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::sign(const T& _val) noexcept
  {
    return _val >= T(0) ? T(1) : T(-1);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::copysign(const T& _mag, const T& _sign) noexcept
  {
    return abs(_mag) * sign(_sign);
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::max(const T& _val1, const T& _val2) noexcept
  {
    return _val1 > _val2 ? _val1 : _val2;
  }

  template<typename T>
  NY_FORCE_INLINE T
  Math::min(const T& _val1, const T& _val2) noexcept
  {
    return _val1 < _val2 ? _val1 : _val2;
  }

  template<typename V, typename F>
  NY_FORCE_INLINE bool
  Math::hasFlag(const V& _val, const F& _flag) noexcept
  {
    return (_val & _flag) == _flag;
  }
}