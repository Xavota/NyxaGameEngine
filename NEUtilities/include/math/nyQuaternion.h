/******************************************************************************/
/**
 * @file    nyQuaternion.hpp
 * @author  Dalia Castellanos
 * @date    15/09/2026
 * @brief   Defines the Quaternion class for 3D rotations.
 *
 * A simple quaternion class for representing 3D rotations.
 *
 * @bug	    No known bugs.
 */
 /******************************************************************************/
#pragma once

#include <string>

#include "nyModuleName.hpp"

#include "macros/nyUtilitiesApi.hpp"
#include "macros/nyMacros.hpp"

#include "types/nyConcepts.hpp"
#include "types/nyContainers.hpp"
#include "types/nyTypes.hpp"
#include "types/nyResult.hpp"

#include "math/nyAngle.h"
#include "math/nyMath.h"
#include "math/nyMatrix4.h"
#include "math/nyVector3.hpp"

namespace nyEngineSDK
{
  /**
   * @brief A simple 4D vector class for geometrical operations.
   * @bug No known bugs
   */
#if NY_CPP20
  template<FloatingPoint T>
#else
  template<typename T>
#endif
  class NY_API Quaternion
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Quaternion<T> requires a floating-point type."
    );
#endif

   public:
    /**
     * @brief The default constructor for a Quaternion object, initializing all
     *        components to zero.
     */
    Quaternion() noexcept : w(T{ 0 }), x(T{ 0 }), y(T{ 0 }), z(T{ 0 }) {}
    /**
     * @brief A constructor for a Quaternion object that initializes it with
     *        the specified components.
     * @param x The x-component of the quaternion.
     * @param y The y-component of the quaternion.
     * @param z The z-component of the quaternion.
     * @param w The w-component of the quaternion.
     */
    Quaternion(T w, T x, T y, T z) noexcept :
    w(w), x(x), y(y), z(z) {}
    /**
     * @brief A constructor for a Quaternion object that initializes it with
     *        the specified rotation axis and angle.
     * @param axis   The rotation axis.
     * @param angle  The twist angle around the axis.
     */
    Quaternion(const Vector3<T>& axis, const Angle<T>& angle) noexcept {
      Vector3<T> normalizedAxis = axis.getNormalized();
      Angle<T> halfAngle = angle / T(2);
      T sinHalfAngle = Math::sin(halfAngle);

      w = Math::cos(halfAngle);
      x = normalizedAxis.x * sinHalfAngle;
      y = normalizedAxis.y * sinHalfAngle;
      z = normalizedAxis.z * sinHalfAngle;
    }

    /**
     * @brief  The dot product of two quaternions.
     * @param  other  The other quaternion for the dot product.
     * @return A new quaternion with
     *         x = x1 * x2, y = y1 * y2, z = z1 * z2, w = w1 * w2.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    dot(const Quaternion<T>& other) const noexcept;

    /**
     * @brief  Returns the square norm of the vector in space.
     * @return The square norm of the vector.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    getSqrNorm() const noexcept;
    /**
     * @brief  Returns the norm of the vector in space.
     * @return The norm of the vector.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    getNorm() const noexcept;
    /**
     * @brief  Returns a vector with the same direction as the original but
     *         length of 1 unit.
     * @return The vector normalized.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    getNormalized() const noexcept;
    /**
     * @brief  Modifies this vector to have length of 1 unit with its same
     *         direction, and returns it.
     * @return This vector normalized.
     */
    NY_FORCE_INLINE Quaternion<T>&
    normalize() noexcept;

    /**
     * @brief  Returns a quaternion with the same direction as the original but
     *         inverted sign for the imaginary components.
     * @return The conjugate quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    getConjugate() const noexcept;
    /**
     * @brief  Modifies this quaternion to have the same direction as the
     *         original but inverted sign for the imaginary components,
     *         and returns it.
     * @return This vector normalized.
     */
    NY_FORCE_INLINE Quaternion<T>&
    conjugate() noexcept;
    /**
     * @brief  Returns the inverse of the quaternion, which is the conjugate
     *         divided by the norm squared.
     * @return The conjugate quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    getInverse() const noexcept;
    /**
     * @brief  Modifies this quaternion to be its inverse, which is the
     *         conjugate divided by the norm squared, and returns it.
     * @return This vector normalized.
     */
    NY_FORCE_INLINE Quaternion<T>&
    invert() noexcept;

    /**
     * @brief  Transforms a vector by this quaternion.
     * @param  v  The vector to transform.
     * @return The transformed vector.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    transform(const Vector3<T>& v) const noexcept;

    /**
     * @brief  Returns the vector part of the quaternion.
     * @return The vector part of the quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    getVectorPart() const noexcept;
    /**
     * @brief  Returns the argument (angle) of the quaternion in radians.
     * @return The argument (angle) of the quaternion in radians.
     */
    NY_FORCE_INLINE NY_NODISCARD Result<Quaternion<T>>
    getArgument() const noexcept;

    /**
     * @brief  Returns the natural logarithm of the quaternion.
     * @return The natural logarithm of the quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    log() const noexcept;
    /**
     * @brief  Returns the logarithm of the quaternion with a specified base.
     * @param  base  The base of the logarithm.
     * @return The logarithm of the quaternion with the specified base.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    log(T base) const noexcept;
    /**
     * @brief  Returns the exponential of the quaternion.
     * @return The exponential of the quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    exp() const noexcept;
    /**
     * @brief  Returns the quaternion raised to a specified power,
     *         using the formula q^exponent = exp(exponent * log(q)).
     * @param  exponent  The power to raise the quaternion to.
     * @return The quaternion raised to the specified power.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    pow(T exponent) const noexcept;

    /**
     * @brief  Spherically interpolates between two quaternions based on the
     *         given alpha value.
     * @param  a      The starting quaternion.
     * @param  b      The ending quaternion.
     * @param  alpha  The interpolation factor (0.0f to 1.0f).
     * @return The interpolated quaternion between a and b.
     */
    static NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    slerp(const Quaternion<T>& a, const Quaternion<T>& b,
          T alpha, bool allowFlip = true) noexcept;
    /**
     * @brief  Spherically interpolates between two quaternions based on the
     *         given alpha value.
     * @param  a           The starting quaternion.
     * @param  b           The ending quaternion.
     * @param  alpha       The interpolation factor (0.0f to 1.0f).
     * @param  _curveFunc  A function that modifies the interpolation factor to
     *                     create a custom interpolation curve.
     * @return The interpolated quaternion between a and b.
     */
    template<typename Curve>
    static NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    slerp(const Quaternion<T>& a, const Quaternion<T>& b,
          T alpha, Curve&& curveFunc, bool allowFlip = true) noexcept;
          
    /**
     * @brief  Returns the inverse of the quaternion, which is the conjugate
     *         divided by the norm squared.
     * @return The conjugate quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    getScaled(T scale) const noexcept;
    /**
     * @brief  Modifies this quaternion to be its inverse, which is the
     *         conjugate divided by the norm squared, and returns it.
     * @return This vector normalized.
     */
    NY_FORCE_INLINE Quaternion<T>&
    scaled(T scale) noexcept;

    /**
     * @brief  Returns the angle between two quaternions in radians.
     * @return The angle between the two quaternions in radians.
     */
    static NY_FORCE_INLINE NY_NODISCARD T
    getAngleBetween(const Quaternion<T>& a, const Quaternion<T>& b) noexcept;
    /**
     * @brief  Returns the angle of rotation represented by this quaternion
     *         in radians.
     * @return The angle of rotation represented by this quaternion in radians.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    getAngle() const noexcept;

    /**
     * @brief  Performs quaternion multiplication, which combines the rotations
     *         of two quaternions.
     * @param  other  The other quaternion for the operation.
     * @return The product of the two quaternions.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    operator*(const Quaternion<T>& other) const noexcept;

    /**
     * @brief  Returns a quaternion in the opposite direction of the original.
     * @return A quaternion in the opposite direction of the original.
     */
    NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
    operator-() const noexcept;
    
    /**
     * @brief  Makes this quaternion the product of itself and another
     *         quaternion.
     * @param  other  The other quaternion for the operation.
     * @return This quaternion after the operation.
     */
    NY_FORCE_INLINE Quaternion<T>&
    operator*=(const Quaternion<T>& other) noexcept;
    
    /**
     * @brief  Check if every component of the quaternion are equal to their
     *         counterpart of the other quaternion.
     * @param  other  The other quaternion to check.
     * @return True if they are equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator==(const Quaternion<T>& other) const noexcept;
    /**
     * @brief  Check if any component of the quaternion is not equal to their
     *         counterpart of the other quaternion.
     * @param  other  The other quaternion to check.
     * @return True if they are not equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator!=(const Quaternion<T>& other) const noexcept;

    /**
     * @brief  Converts this quaternion to a quaternion of another type.
     * @tparam U The type to which the quaternion should be converted.
     * @return A new quaternion of type U with the same components as this quaternion.
     */
    template<typename U>
    explicit NY_FORCE_INLINE NY_NODISCARD
    operator Quaternion<U>() const noexcept;

    /**
     * @brief  Converts this quaternion to its respective Euler angles
     *         representation.
     * @return The Euler angles representing the same rotation as this quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD EulerAngles<T>
    toEulerAngles() const noexcept;
    /**
     * @brief  Converts this quaternion to its respective transformation matrix
     *         representation.
     * @return The transformation matrix representing the same rotation as this
     *         quaternion.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
    toMatrix() const noexcept;

    /**
     * @brief  Creates and returns a string with the format
     *         "(w + xi + yj + zk)".
     * @return This vector as a String.
     */
    NY_FORCE_INLINE NY_NODISCARD String
    toString() noexcept;

    /**
     * @brief The components of the quaternion, in a union so they can be taken
     *        separately or together
     */
    union
    {
      struct
      {
        /*
         * @brief The w component of the quaternion
         */
        T w;
        /*
         * @brief The x component of the quaternion
         */
        T x;
        /*
         * @brief The y component of the quaternion
         */
        T y;
        /*
         * @brief The z component of the quaternion
         */
        T z;
      };
      /*
       * @brief All the components of the quaternion in an array
       */
      Array<T, 4> wxyz;
    };

    /*
     * @brief A quaternion with 0 as its components
     */
    inline static const Quaternion kZERO{ T{0}, T{0}, T{0}, T{0} };
    /*
     * @brief A unitary quaternion pointing forward
     */
    inline static const Quaternion kFORWARD{ T{0}, T{0}, T{0}, T{1} };
    /*
     * @brief A unitary quaternion pointing right
     */
    inline static const Quaternion kRIGHT{ T{0}, T{1}, T{0}, T{0} };
    /*
     * @brief A unitary quaternion pointing up
     */
    inline static const Quaternion kUP{ T{0}, T{0}, T{1}, T{0} };
    /*
     * @brief The identity quaternion, representing no rotation
     */
    inline static const Quaternion kIDENTITY{ T{1}, T{0}, T{0}, T{0} };
  };

  using Quaternionf = Quaternion<f32>;
  using Quaterniond = Quaternion<f64>;

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Quaternion<T>::dot(const Quaternion<T>& other) const noexcept
  {
    T x1 = this->x;
    T y1 = this->y;
    T z1 = this->z;
    T w1 = this->w;

    T x2 = other.x;
    T y2 = other.y;
    T z2 = other.z;
    T w2 = other.w;

    return x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Quaternion<T>::getSqrNorm() const noexcept
  {
    return w * w + x * x + y * y + z * z;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Quaternion<T>::getNorm() const noexcept
  {
    return Math::sqrt<T>(getSqrNorm<T>());
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::getNormalized() const noexcept
  {
    const T magnitude = getNorm<T>();
    if (magnitude < Math::kTinyFloat<T>)
    {
      return Quaternion<T>::kZERO;
    }
    return Quaternion<T>(this->w / magnitude, this->x / magnitude,
                         this->y / magnitude, this->z / magnitude);
  }
  template<typename T>
  NY_FORCE_INLINE Quaternion<T>&
  Quaternion<T>::normalize() noexcept
  {
    *this = getNormalized();
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::getConjugate() const noexcept
  {
    return Quaternion<T>(this->w, -this->x, -this->y, -this->z);
  }

  template<typename T>
  NY_FORCE_INLINE Quaternion<T>&
  Quaternion<T>::conjugate() noexcept
  {
    *this = getConjugate();
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::getInverse() const noexcept
  {
    T normSquared = getSqrNorm();
    if (normSquared < Math::kTinyFloat<T>)
    {
      return Quaternion<T>::kZERO;
    }
    Quaternion<T> conjugate = getConjugate();
    return Quaternion<T>(conjugate.w / normSquared, conjugate.x / normSquared,
                         conjugate.y / normSquared, conjugate.z / normSquared);
  }

  template<typename T>
  NY_FORCE_INLINE Quaternion<T>&
  Quaternion<T>::invert() noexcept
  {
    *this = getInverse();
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Quaternion<T>::transform(const Vector3<T>& v) const noexcept
  {
    Quaternion<T> p(0, v.x, v.y, v.z);
    Quaternion r = *this * p * getInverse();
    return Vector3<T>(r.x, r.y, r.z);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Quaternion<T>::getVectorPart() const noexcept
  {
    return Vector3<T>(this->x, this->y, this->z);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Quaternion<T>>
  Quaternion<T>::getArgument() const noexcept
  {
    T norm = getNorm();
    if (norm < Math::kTinyFloat<T>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Can't get argument of zero quaternion");
    }
    return Math::acos(w / norm);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::log() const noexcept
  {
    T m = getVectorPart().getMagnitude();
    T t = m < Math::kTinyFloat<T> ? T(0) : Math::atan2(m, w) / m;

    Quaternion<T> r;

    r.w = T(0.5) * Math::log(getSqrNorm());
    r.x = x * t;
    r.y = y * t;
    r.z = z * t;
    return r;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::log(T base) const noexcept
  {
    return log().getScaled(T(1) / Math::log(base));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::exp() const noexcept
  {
    T m = getVectorPart().getMagnitude();
    T et = Math::exp(w);
    T s = m < Math::kTinyFloat<T> ? T(0) : et * Math::sin(m) / m;

    Quaternion<T> r;
    r.w = et * Math::cos(m);
    r.x = x * s;
    r.y = y * s;
    r.z = z * s;
    return r;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::pow(T exponent) const noexcept
  {
    return log().getScaled(exponent).exp();
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::slerp(const Quaternion<T>& a, const Quaternion<T>& b,
                       T alpha, bool allowFlip) noexcept
  {
    T cosAngle = a.dot(b);

    T c1, c2;
    // Linear interpolation for close orientations
    if ((T(1) - Math::abs(cosAngle)) < Math::kSmallFloat<T>) {
      c1 = T(1) - alpha;
      c2 = alpha;
    }
    else {
      // Spherical interpolation
      T angle = Math::acos(Math::abs(cosAngle));
      T sinAngle = Math::sin(angle);
      c1 = Math::sin(angle * (T(1) - alpha)) / sinAngle;
      c2 = Math::sin(angle * alpha) / sinAngle;
    }

    // Use the shortest path
    if (allowFlip && (cosAngle < 0.0))
      c1 = -c1;

    Quaternion<T> r;

    r.w = c1 * a.w + c2 * b.w;
    r.x = c1 * a.x + c2 * b.x;
    r.y = c1 * a.y + c2 * b.y;
    r.z = c1 * a.z + c2 * b.z;

    return r;
  }
  template<typename T>
  template<typename Curve>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::slerp(const Quaternion<T>& a, const Quaternion<T>& b,
                       T alpha, Curve&& curveFunc, bool allowFlip) noexcept
  {
    T modifiedAlpha = Math::lerp(T(0), T(1), alpha, curveFunc);
    return Quaternion<T>::slerp(a, b, modifiedAlpha, allowFlip);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::getScaled(T scale) const noexcept
  {
    return Quaternion<T>(this->w * scale, this->x * scale,
                         this->y * scale, this->z * scale);
  }

  template<typename T>
  NY_FORCE_INLINE Quaternion<T>&
  Quaternion<T>::scaled(T scale) noexcept
  {
    *this = getScaled(scale);
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Quaternion<T>::getAngleBetween(const Quaternion<T>& a, const Quaternion<T>& b) noexcept
  {
    return Math::acos(a.dot(b));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Quaternion<T>::getAngle() const noexcept
  {
    return Math::acos(w);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::operator*(const Quaternion<T>& other) const noexcept
  {
    return Quaternion<T>(this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
                         this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
                         this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
                         this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Quaternion<T>
  Quaternion<T>::operator-() const noexcept
  {
    return Quaternion<T>(-this->x, -this->y, -this->z, -this->w);
  }

  template<typename T>
  NY_FORCE_INLINE Quaternion<T>&
  Quaternion<T>::operator*=(const Quaternion<T>& other) noexcept
  {
    *this = *this * other;
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD bool
  Quaternion<T>::operator==(const Quaternion<T>& other) const noexcept
  {
    return this->x == other.x && this->y == other.y &&
           this->z == other.z && this->w == other.w;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD bool
  Quaternion<T>::operator!=(const Quaternion<T>& other) const noexcept
  {
    return !(*this == other);
  }

  template<typename T>
  template<typename U>
  Quaternion<T>::operator Quaternion<U>() const noexcept
  {
    return Quaternion<U>(static_cast<U>(x),
                         static_cast<U>(y),
                         static_cast<U>(z),
                         static_cast<U>(w));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD EulerAngles<T>
  Quaternion<T>::toEulerAngles() const noexcept
  {
    EulerAngles<T> r;
    r.pitch = Math::atan2(T(2) * (w * x + y * z), T(1) - T(2) * (x * x + y * y));
    r.yaw   = Math::asin (T(2) * (w * y - z * x));
    r.roll  = Math::atan2(T(2) * (w * z + x * y), T(1) - T(2) * (y * y + z * z));
    return r;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Quaternion<T>::toMatrix() const noexcept
  {
    Matrix4<T> r;

    r.m00 = 1 - 2 * (y * y + z * z);
    r.m10 =     2 * (x * y - z * w);
    r.m20 =     2 * (x * z + y * w);

    r.m01 =     2 * (x * y + z * w);
    r.m11 = 1 - 2 * (x * x + z * z);
    r.m21 =     2 * (y * z - x * w);

    r.m02 =     2 * (x * z - y * w);
    r.m12 =     2 * (y * z + x * w);
    r.m22 = 1 - 2 * (x * x + y * y);

    r.m03 = r.m13 = r.m23 = 0;//right column
    r.m30 = r.m31 = r.m32 = 0;//bottom row
    r.m33 = 1;//bottom right

    return r;
  }

  template<typename T>
  NY_FORCE_INLINE String
  Quaternion<T>::toString() noexcept
  {
    return "(" + std::to_string(this->w) +
           " " + (this->x < T(0) ? "-" : "+") + " " +
           std::to_string(Math::abs(this->x)) + "i " +
           (this->y < T(0) ? "-" : "+") + " " +
           std::to_string(Math::abs(this->y)) + "j " +
           (this->z < T(0) ? "-" : "+") + " " +
           std::to_string(Math::abs(this->z)) + "k)";
  }
} // namespace nyEngineSDK