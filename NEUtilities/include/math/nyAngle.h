#pragma once

#include "nyModuleName.hpp"

#include "macros/nyMacros.hpp"
#include "macros/nyCompiler.hpp"


#include "math/nyMath.h"

#include "types/nyResult.hpp"

namespace nyEngineSDK
{
#if NY_CPP20
  template<FloatingPoint T>
#else
  template<typename T>
#endif
  class Angle
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Angle<T> requires a floating-point type."
    );
#endif

   public:
    /**
     * @brief  Constructs an Angle object with the specified angle in degrees.
     * @param  _degree  The angle in degrees.
     * @return An Angle object representing the specified angle.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    degrees(T _degree) noexcept
    {
      Angle a;
      a.angle = Math::degToRad(_degree);
      return a;
    }
    /**
     * @brief  Constructs an Angle object with the specified angle in radians.
     * @param  _radian  The angle in radians.
     * @return An Angle object representing the specified angle.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    radians(T _radian) noexcept
    {
      Angle a;
      a.angle = _radian;
      return a;
    }

    /**
     * @brief  Adds two Angle objects together.
     * @param  other  The other Angle object to add.
     * @return A new Angle object representing the sum of the two angles.
     */
    NY_FORCE_INLINE NY_NODISCARD Angle
    operator+(const Angle& other) const noexcept
    {
      Angle a;
      a.angle = angle + other.angle;
      return a;
    }
    /**
     * @brief  Subtracts one Angle object from another.
     * @param  other  The other Angle object to subtract.
     * @return A new Angle object representing the difference of the two angles.
     */
    NY_FORCE_INLINE NY_NODISCARD Angle
    operator-(const Angle& other) const noexcept
    {
      Angle a;
      a.angle = angle - other.angle;
      return a;
    }
    /**
     * @brief  Multiplies an Angle object by a scalar value.
     * @param  scale  The scalar value to multiply the angle by.
     * @return A new Angle object representing the scaled angle.
     */ 
    NY_FORCE_INLINE NY_NODISCARD Angle
    operator*(const T scale) const noexcept
    {
      Angle a;
      a.angle = angle * scale;
      return a;
    }
    /**
     * @brief  Divides an Angle object by a scalar value.
     * @param  scale  The scalar value to divide the angle by.
     * @return A new Angle object representing the scaled angle.
     */
    NY_FORCE_INLINE NY_NODISCARD Angle
    operator/(const T scale) const noexcept
    {
      Angle a;
      a.angle = angle / scale;
      return a;
    }

    /**
     * @brief  Divides an Angle object by a scalar value.
     * @param  scale  The scalar value to divide the angle by.
     * @return A new Result<Angle> object representing the scaled angle, or an
     *         error status if division by zero is attempted.
     */
    NY_FORCE_INLINE NY_NODISCARD Result<Angle>
    tryDivide(const T scale) const noexcept
    {
      if (Math::abs(scale) < Math::kFLOAT_TINY)
      {
        return Status::error(LogLevel::Warning, kModule, "Division by zero is not allowed.");
      }
      Angle a;
      a.angle = angle / scale;
      return a;
    }

    /**
     * @brief  Adds another Angle object to this Angle object.
     * @param  other  The other Angle object to add.
     * @return A reference to this Angle object after the addition.
     */
    NY_FORCE_INLINE NY_NODISCARD Angle&
    operator+=(const Angle& other) noexcept
    {
      this->angle = angle + other.angle;
      return *this;
    }
    /**
     * @brief  Subtracts another Angle object from this Angle object.
     * @param  other  The other Angle object to subtract.
     * @return A reference to this Angle object after the subtraction.
     */
    NY_FORCE_INLINE NY_NODISCARD Angle&
    operator-=(const Angle& other) noexcept
    {
      this->angle = angle - other.angle;
      return *this;
    }
    /**
     * @brief  Multiplies this Angle object by a scalar value.
     * @param  scale  The scalar value to multiply the angle by.
     * @return A reference to this Angle object after the multiplication.
     */
    NY_FORCE_INLINE NY_NODISCARD Angle&
    operator*=(const T scale) noexcept
    {
      this->angle = angle * scale;
      return *this;
    }
    /**
     * @brief  Divides this Angle object by a scalar value.
     * @param  scale  The scalar value to divide the angle by.
     * @return A reference to this Angle object after the division.
     */
    NY_FORCE_INLINE NY_NODISCARD Angle&
    operator/=(const T scale) noexcept
    {
      this->angle = angle / scale;
      return *this;
    }

    /**
     * @brief  Explicit conversion operator to T. Allows an Angle object to be
     *         converted to a floating-point value representing the angle in
     *         radians.
     * @return The angle in radians as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD explicit
    operator T() const noexcept
    {
      return angle;
    }

    /**
     * @brief  Converts this vector to a vector of another type.
     * @tparam U The type to which the vector should be converted.
     * @return A new vector of type U with the same components as this vector.
     */
#if NY_CPP20
    template<FloatingPoint U>
#else
    template<typename U>
#endif
    explicit NY_FORCE_INLINE NY_NODISCARD
    operator Angle<U>() const noexcept
    {
      return Angle<U>::radians(static_cast<U>(angle));
    }

    /**
     * @brief  Returns the angle in degrees.
     * @return The angle in degrees as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    toDegrees() const noexcept
    {
      return Math::radToDeg(angle);
    }
    /**
     * @brief  Returns the angle in radians.
     * @return The angle in radians as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    toRadians() const noexcept
    {
      return angle;
    }

    /**
     * @brief  Returns the cosine of an angle.
     * @return The cosine of the angle as a floating-point value.
     */
    static NY_FORCE_INLINE NY_NODISCARD T
    cos(const Angle& a) noexcept
    {
      return Math::cos(a.angle);
    }
    /**
     * @brief  Returns the sine of an angle.
     * @return The sine of the angle as a floating-point value.
     */
    static NY_FORCE_INLINE NY_NODISCARD T
    sin(const Angle& a) noexcept
    {
      return Math::sin(a.angle);
    }
    /**
     * @brief  Returns the tangent of an angle.
     * @return The tangent of the angle as a floating-point value.
     */
    static NY_FORCE_INLINE NY_NODISCARD T
    tan(const Angle& a) noexcept
    {
      return Math::tan(a.angle);
    }

    /**
     * @brief  Returns the secant of an angle.
     * @return The secant of the angle as a floating-point value.
     */
    static NY_FORCE_INLINE NY_NODISCARD T
    sec(const Angle& a) noexcept
    {
      return Math::sec(a.angle);
    }
    /**
     * @brief  Returns the cosecant of an angle.
     * @return The cosecant of the angle as a floating-point value.
     */
    static NY_FORCE_INLINE NY_NODISCARD T
    csc(const Angle& a) noexcept
    {
      return Math::csc(a.angle);
    }
    /**
     * @brief  Returns the cotangent of an angle.
     * @return The cotangent of the angle as a floating-point value.
     */
    static NY_FORCE_INLINE NY_NODISCARD T
    cot(const Angle& a) noexcept
    {
      return Math::cot(a.angle);
    }

    /**
     * @brief  Returns the arccosine of a value as an Angle object.
     * @param  value  The value for which to compute the arccosine.
     * @return An Angle object representing the arccosine of the value.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    acos(T value) noexcept
    {
      return Angle::radians(Math::acos(value));
    }
    /**
     * @brief  Returns the arcsine of a value as an Angle object.
     * @param  value  The value for which to compute the arcsine.
     * @return An Angle object representing the arcsine of the value.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    asin(T value) noexcept
    {
      return Angle::radians(Math::asin(value));
    }
    /**
     * @brief  Returns the arctangent of a value as an Angle object.
     * @param  value  The value for which to compute the arctangent.
     * @return An Angle object representing the arctangent of the value.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    atan(T value) noexcept
    {
      return Angle::radians(Math::atan(value));
    }
    /**
     * @brief  Returns the arctangent of y/x as an Angle object.
     * @param  y  The y-coordinate.
     * @param  x  The x-coordinate.
     * @return An Angle object representing the arctangent of y/x.
     */ 
    static NY_FORCE_INLINE NY_NODISCARD Angle
    atan2(T y, T x) noexcept
    {
      return Angle::radians(Math::atan2(y, x));
    }

    /**
     * @brief  Returns the arcsecant of a value as an Angle object.
     * @param  value  The value for which to compute the arcsecant.
     * @return An Angle object representing the arcsecant of the value.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    asec(T value) noexcept
    {
      return Angle::radians(Math::asec(value));
    } 
    /**
     * @brief  Returns the arccosecant of a value as an Angle object.
     * @param  value  The value for which to compute the arccosecant.
     * @return An Angle object representing the arccosecant of the value.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    acsc(T value) noexcept
    {
      return Angle::radians(Math::acsc(value));
    }
    /**
     * @brief  Returns the arccotangent of a value as an Angle object.
     * @param  value  The value for which to compute the arccotangent.
     * @return An Angle object representing the arccotangent of the value.
     */
    static NY_FORCE_INLINE NY_NODISCARD Angle
    acot(T value) noexcept
    {
      return Angle::radians(Math::acot(value));
    }

    /**
     * @brief  Returns the cosine of the angle.
     * @return The cosine of the angle as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    cos() const noexcept
    {
      return Math::cos(angle);
    }
    /**
     * @brief  Returns the sine of the angle.
     * @return The sine of the angle as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    sin() const noexcept
    {
      return Math::sin(angle);
    }
    /**
     * @brief  Returns the tangent of the angle.
     * @return The tangent of the angle as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    tan() const noexcept
    {
      return Math::tan(angle);
    }

    /**
     * @brief  Returns the secant of the angle.
     * @return The secant of the angle as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    sec() const noexcept
    {
      return Math::sec(angle);
    }
    /**
     * @brief  Returns the cosecant of the angle.
     * @return The cosecant of the angle as a floating-point value.
     */ 
    NY_FORCE_INLINE NY_NODISCARD T
    csc() const noexcept
    {
      return Math::csc(angle);
    }
    /**
     * @brief  Returns the cotangent of the angle.
     * @return The cotangent of the angle as a floating-point value.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    cot() const noexcept
    {
      return Math::cot(angle);
    }

   private:
    /**
     * @brief The angle value in radians.
     */
    T angle = 0.0f;
  };

  using AngleF = Angle<float>;
  using AngleD = Angle<double>;

  template<typename T>
  struct EulerAngles
  {
    Angle<T> pitch;
    Angle<T> yaw;
    Angle<T> roll;
  };
}