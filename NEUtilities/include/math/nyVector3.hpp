/******************************************************************************/
/**
 * @file    nyVector3.hpp
 * @author  Dalia Castellanos
 * @date    02/09/2026
 * @brief   Defines the Vector3 class for geometrical operations.
 *
 * A simple 3D vector class for geometrical operations.
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
#include "types/nyStatus.hpp"
#include "types/nyResult.hpp"

#include "math/nyMath.h"

namespace nyEngineSDK
{
  /**
   * @brief A simple 3D vector class for geometrical operations.
   * @bug No known bugs
   */
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  class NY_API Vector3
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsNumberV<T>,
      "Vector3<T> requires a number type."
    );
#endif

   public:
    /**
     * @brief The default constructor for a Vector3 object, initializing all
     *        components to zero.
     */
    Vector3() noexcept : x(T{ 0 }), y(T{ 0 }), z(T{ 0 }) {}
    /**
     * @brief A constructor for a Vector3 object that initializes the vector
     *        with the specified components.
     * @param x The x-component of the vector.
     * @param y The y-component of the vector.
     * @param z The z-component of the vector.
     */
    Vector3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}
    /**
     * @brief A constructor for a Vector3 object that initializes the vector
     *        with the specified direction and scale.
     * @param dir   The direction vector.
     * @param scale The scale factor.
     */
    Vector3(const Vector3<T>& dir, T scale) noexcept :
    x(dir.x * scale), y(dir.y * scale), z(dir.z * scale) {}

    /**
     * @brief  The dot product of two vectors.
     * @param  other  The other vector for the dot product.
     * @return A new vector with x = x1 * x2, y = y1 * y2, z = z1 * z2.
     */
    template<typename R = T>
    NY_FORCE_INLINE NY_NODISCARD R
    dot(const Vector3<T>& other) const noexcept;
    /**
     * @brief  The cross product of two vectors.
     * @param  other  The other vector for the cross product.
     * @return The result of the cross product of the two vectors.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    cross(const Vector3<T>& other) const noexcept;
    
    /**
     * @brief  The square distance between two points.
     * @param  other  The other point for the distance calculation.
     * @return The square distance between this point and the other point.
     */
    template<typename R = T>
    NY_FORCE_INLINE NY_NODISCARD R
    getSqrDistance(const Vector3<T>& other) const noexcept;
    /**
     * @brief  The distance between two points.
     * @param  other  The other point for the distance calculation.
     * @return The distance between this point and the other point.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    NY_FORCE_INLINE NY_NODISCARD R
    getDistance(const Vector3<T>& other) const noexcept;
    /**
     * @brief  Returns the square length of the vector in space.
     * @return The square length of the vector.
     */
    template<typename R = T>
    NY_FORCE_INLINE NY_NODISCARD R
    getSqrMagnitude() const noexcept;
    /**
     * @brief  Returns the length of the vector in space.
     * @return The length of the vector.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    NY_FORCE_INLINE NY_NODISCARD R
    getMagnitude() const noexcept;
    /**
     * @brief  Returns a vector with the same direction as the original but
     *         length of 1 unit.
     * @return The vector normalized.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    getNormalized() const noexcept
#if NY_CPP20
    requires FloatingPoint<T>
#endif
    ;
    /**
     * @brief  Modifies this vector to have length of 1 unit with its same
     *         direction, and returns it.
     * @return This vector normalized.
     */
    NY_FORCE_INLINE Vector3<T>
    normalize() noexcept
#if NY_CPP20
    requires FloatingPoint<T>
#endif
    ;
    /**
     * @brief  Returns a vector with the same direction as the original
     *         but with the new size given.
     * @param  newSize  The desired size of the new vector.
     * @return The vector truncated with the new size.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    NY_FORCE_INLINE NY_NODISCARD Vector3<R>
    getTruncated(R newSize) const noexcept;
    /**
     * @brief  Modifies this vector to have the same direction as the original
     *         but with the new size given and returns it.
     * @param  newSize  The desired size of the new vector.
     * @return This vector truncated with the new size.
     */
    NY_FORCE_INLINE Vector3<T>
    truncate(T newSize) noexcept
#if NY_CPP20
    requires FloatingPoint<T>
#endif
    ;

    /**
     * @brief  Returns a vector that is the projection of a over the vector b
     * @param  a  The vector to project.
     * @param  b  The vector onto which to project.
     * @return The projected vector.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector3<R>>
    projection(const Vector3<T>& a, const Vector3<T>& b) noexcept;
    /**
     * @brief  Returns a vector that is the rejection of a over the vector b
     * @param  a  The vector to reject.
     * @param  b  The vector onto which to reject.
     * @return The rejected vector.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector3<R>>
    rejection(const Vector3<T>& a, const Vector3<T>& b) noexcept;
    /**
     * @brief  Returns a vector that is the reflection of a with respect to the
     *         normal vector b
     * @param  a  The vector to reflect.
     * @param  b  The normal vector about which to reflect.
     * @return The reflected vector.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector3<R>>
    reflection(const Vector3<T>& a, const Vector3<T>& b) noexcept;

    /**
     * @brief  Linearly interpolates between two vectors based on the given
     *         alpha value.
     * @param  a      The starting vector.
     * @param  b      The ending vector.
     * @param  alpha  The interpolation factor (0.0f to 1.0f).
     * @return The interpolated vector between a and b.
     */
    template<typename Alpha = ConditionalT<IsIntegerV<T>, f32, T>>
    static NY_FORCE_INLINE NY_NODISCARD Vector3<Alpha>
    lerp(const Vector3<T>& a, const Vector3<T>& b, Alpha alpha) noexcept;
    /**
     * @brief  Linearly interpolates between two vectors based on the given
     *         alpha value.
     * @param  a           The starting vector.
     * @param  b           The ending vector.
     * @param  alpha       The interpolation factor (0.0f to 1.0f).
     * @param  _curveFunc  A function that modifies the interpolation factor to
     *                     create a custom interpolation curve.
     * @return The interpolated vector between a and b.
     */
    template<typename Alpha = ConditionalT<IsIntegerV<T>, f32, T>,
             typename Curve>
    static NY_FORCE_INLINE NY_NODISCARD Vector3<Alpha>
    lerp(const Vector3<T>& a, const Vector3<T>& b,
         Alpha alpha, Curve&& curveFunc) noexcept;

    /**
     * @brief  Creates and returns a string with the format "{ x:0, y:0, z:0 }".
     * @return This vector as a String.
     */
    NY_FORCE_INLINE NY_NODISCARD String
    toString() const noexcept;

    /**
     * @brief  Returns a vector with the sum of every component of the original
     *         plus their counterpart on the other vector.
     * @param  other  The other vector for the operation.
     * @return The sum of the two vectors.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    operator+(const Vector3<T>& other) const noexcept;
    /**
     * @brief  Returns a vector with the subtraction of every component of the
     *         original minus their counterpart on the other vector.
     * @param  other  The other vector for the operation.
     * @return The subtraction of the two vectors.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    operator-(const Vector3<T>& other) const noexcept;

    /**
     * @brief  Returns a vector with the sum of every component of the original
     *         plus the given number.
     * @param  other  The number for the operation.
     * @return The sum of the vector plus the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    operator+(T other) const noexcept;
    /**
     * @brief  Returns a vector with the subtraction of every component of the
     *         original minus the given number.
     * @param  other  The number for the operation.
     * @return The subtraction of the vector minus the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    operator-(T other) const noexcept;
    /**
     * @brief  Returns a vector with the multiplication of every component of the original
     *         by the given number.
     * @param  other  The number for the operation.
     * @return The product of the vector and the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    operator*(T other) const noexcept;
    /**
     * @brief  Returns a vector with the division of every component of the
     *         original by the given number.
     * @param  other  The number for the operation.
     * @return The division of the vector by the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    operator/(T other) const noexcept;

    /**
     * @brief  Returns a vector in the opposite direction of the original.
     * @return A vector in the opposite direction of the original.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    operator-() const noexcept;
    
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of itself plus their counterparts of the other vector.
     * @param  other  The other vector to whom is gonna be sum.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector3<T>&
    operator+=(const Vector3<T>& other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of itself minus their counterparts of the other vector.
     * @param  other  The other vector to whom is gonna be subtracted.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector3<T>&
    operator-=(const Vector3<T>& other) noexcept;

    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self plus the number.
     * @param  other  The number to whom is gonna be sum.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector3<T>&
    operator+=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self minus the number.
     * @param  other  The number to whom is gonna be subtracted.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector3<T>&
    operator-=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self times the number.
     * @param  other  The number to whom is gonna be multiplied.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector3<T>&
    operator*=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self divided by the number.
     * @param  other  The number to whom is gonna be divided.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector3<T>&
    operator/=(T other) noexcept;
    
    /**
     * @brief  Check if every component of the vector are equal to their
     *         counterpart of the other vector.
     * @param  other  The other vector to check.
     * @return True if they are equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator==(const Vector3<T>& other) const noexcept;
    /**
     * @brief  Check if any component of the vector is not equal to their
     *         counterpart of the other vector.
     * @param  other  The other vector to check.
     * @return True if they are not equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator!=(const Vector3<T>& other) const noexcept;

    /**
     * @brief  Converts this vector to a vector of another type.
     * @tparam U The type to which the vector should be converted.
     * @return A new vector of type U with the same components as this vector.
     */
    template<typename U>
    explicit NY_FORCE_INLINE NY_NODISCARD
    operator Vector3<U>() const noexcept;

    /**
     * @brief  Returns a reference to the component of the vector at
     *         the given index.
     * @param  index  The index of the component to return.
     * @return A reference to the component at the given index.
     */
    NY_FORCE_INLINE NY_NODISCARD T&
    operator[](usize index) noexcept;

    /**
     * @brief  Returns a const reference to the component of the vector a
     *         the given index.
     * @param  index  The index of the component to return.
     * @return A const reference to the component at the given index.
     */
    NY_FORCE_INLINE NY_NODISCARD const T&
    operator[](usize index) const noexcept;

    /*
     * @brief The x component of the vector
     */
    T x;
    /*
     * @brief The y component of the vector
     */
    T y;
    /*
     * @brief The z component of the vector
     */
    T z;

    /*
     * @brief A vector with 0 as its components
     */
    static const Vector3 kZERO;
    /*
     * @brief A unitary vector pointing forward
     */
    static const Vector3 kFORWARD;
    /*
     * @brief A unitary vector pointing right
     */
    static const Vector3 kRIGHT;
    /*
     * @brief A unitary vector pointing up
     */
    static const Vector3 kUP;
  };

  using Vector3f = Vector3<f32>;
  using Vector3i = Vector3<i32>;
  using Vector3u = Vector3<u32>;

  template<typename T>
  inline const Vector3<T> Vector3<T>::kZERO{ T{0}, T{0}, T{0} };
  template<typename T>
  inline const Vector3<T> Vector3<T>::kFORWARD{ T{0}, T{0}, T{1} };
  template<typename T>
  inline const Vector3<T> Vector3<T>::kRIGHT{ T{1}, T{0}, T{0} };
  template<typename T>
  inline const Vector3<T> Vector3<T>::kUP{ T{0}, T{1}, T{0} };

  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector3<T>::dot(const Vector3<T>& other) const noexcept
  {
    R x1 = static_cast<R>(this->x);
    R y1 = static_cast<R>(this->y);
    R z1 = static_cast<R>(this->z);

    R x2 = static_cast<R>(other.x);
    R y2 = static_cast<R>(other.y);
    R z2 = static_cast<R>(other.z);

    return x1 * x2 + y1 * y2 + z1 * z2;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::cross(const Vector3<T>& other) const noexcept
  {
    return Vector3<T>(this->y * other.z - this->z * other.y,
                      this->z * other.x - this->x * other.z,
                      this->x * other.y - this->y * other.x);
  }

  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector3<T>::getSqrDistance(const Vector3<T>& other) const noexcept
  {
    R x1 = static_cast<R>(this->x);
    R y1 = static_cast<R>(this->y);
    R z1 = static_cast<R>(this->z);

    R x2 = static_cast<R>(other.x);
    R y2 = static_cast<R>(other.y);
    R z2 = static_cast<R>(other.z);

    return Math::sqr<R>(x2 - x1) + Math::sqr<R>(y2 - y1) + Math::sqr<R>(z2 - z1);
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector3<T>::getDistance(const Vector3<T>& other) const noexcept
  {
    return Math::sqrt<R>(getSqrDistance<R>(other));
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector3<T>::getSqrMagnitude() const noexcept
  {
    return dot<R>(*this);
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector3<T>::getMagnitude() const noexcept
  {
    return Math::sqrt<R>(getSqrMagnitude<R>());
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::getNormalized() const noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector3<T>::getNormalized() requires a floating-point type."
    );
#endif

    const T magnitude = getMagnitude();
    if (magnitude < Math::kTinyFloat<T>)
    {
      return Vector3<T>::kZERO;
    }
    return Vector3<T>(this->x / magnitude, this->y / magnitude, this->z / magnitude);
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>
  Vector3<T>::normalize() noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector3<T>::normalize() requires a floating-point type."
    );
#endif

    *this = getNormalized();
    return *this;
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Vector3<R>
  Vector3<T>::getTruncated(R newSize) const noexcept
  {
    const R magnitude = getMagnitude<R>();
    if (magnitude < Math::kTinyFloat<R>)
    {
      return Vector3<R>::kZERO;
    }
    return static_cast<Vector3<R>>(*this) * (newSize / magnitude);
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>
  Vector3<T>::truncate(T newSize) noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector3<T>::truncate() requires a floating-point type."
    );
#endif

    *this = getTruncated(newSize);
    return *this;
  }

  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector3<R>>
  Vector3<T>::projection(const Vector3<T>& a, const Vector3<T>& b) noexcept
  {
    const R sqrMagnitude = b.getSqrMagnitude<R>();
    if (sqrMagnitude < Math::kTinyFloat<R>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Cannot project vector onto zero vector.");
    }
    auto aCast = static_cast<Vector3<R>>(a);
    auto bCast = static_cast<Vector3<R>>(b);
    return bCast * (aCast.dot(bCast) / sqrMagnitude);
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector3<R>>
  Vector3<T>::rejection(const Vector3<T>& a, const Vector3<T>& b) noexcept
  {
    auto projResult = projection<R>(a, b);
    if (projResult)
    {
      return static_cast<Vector3<R>>(a) - projResult.value();
    }
    return projResult;
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector3<R>>
  Vector3<T>::reflection(const Vector3<T>& a, const Vector3<T>& b) noexcept
  {
    const R sqrMagnitude = b.getSqrMagnitude<R>();
    if (sqrMagnitude < Math::kTinyFloat<R>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Cannot reflect vector with zero normal.");
    }
    auto aCast = static_cast<Vector3<R>>(a);
    auto bCast = static_cast<Vector3<R>>(b);
    return aCast - (bCast * (R(2) * aCast.dot(bCast) / sqrMagnitude));
  }

  template<typename T>
  template<typename Alpha>
  NY_FORCE_INLINE NY_NODISCARD Vector3<Alpha>
  Vector3<T>::lerp(const Vector3<T>& a, const Vector3<T>& b, Alpha alpha) noexcept
  {
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Alpha must be a floating-point type."
    );

    Alpha x1 = static_cast<Alpha>(a.x);
    Alpha y1 = static_cast<Alpha>(a.y);
    Alpha z1 = static_cast<Alpha>(a.z);

    Alpha x2 = static_cast<Alpha>(b.x);
    Alpha y2 = static_cast<Alpha>(b.y);
    Alpha z2 = static_cast<Alpha>(b.z);

    return Vector3<Alpha>(Math::lerp<Alpha>(x1, x2, alpha),
                          Math::lerp<Alpha>(y1, y2, alpha),
                          Math::lerp<Alpha>(z1, z2, alpha));
  }
  template<typename T>
  template<typename Alpha, typename Curve>
  NY_FORCE_INLINE NY_NODISCARD Vector3<Alpha>
  Vector3<T>::lerp(const Vector3<T>& a, const Vector3<T>& b,
                   Alpha alpha, Curve&& curveFunc) noexcept
  {
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Alpha must be a floating-point type."
    );

    Alpha x1 = static_cast<Alpha>(a.x);
    Alpha y1 = static_cast<Alpha>(a.y);
    Alpha z1 = static_cast<Alpha>(a.z);

    Alpha x2 = static_cast<Alpha>(b.x);
    Alpha y2 = static_cast<Alpha>(b.y);
    Alpha z2 = static_cast<Alpha>(b.z);

    return Vector3<Alpha>(Math::lerp<Alpha>(x1, x2, alpha, curveFunc),
                          Math::lerp<Alpha>(y1, y2, alpha, curveFunc),
                          Math::lerp<Alpha>(z1, z2, alpha, curveFunc));
  }

  template<typename T>
  NY_FORCE_INLINE String
  Vector3<T>::toString() const noexcept
  {
    return "{ x:" + std::to_string(this->x) +
           ", y:" + std::to_string(this->y) +
           ", z:" + std::to_string(this->z) + " }";
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::operator+(const Vector3<T>& other) const noexcept
  {
    return Vector3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::operator-(const Vector3<T>& other) const noexcept
  {
    return Vector3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::operator+(T other) const noexcept
  {
    return Vector3<T>(this->x + other, this->y + other, this->z + other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::operator-(T other) const noexcept
  {
    return Vector3<T>(this->x - other, this->y - other, this->z - other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::operator*(T other) const noexcept
  {
    return Vector3<T>(this->x * other, this->y * other, this->z * other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::operator/(T other) const noexcept
  {
    return Vector3<T>(this->x / other, this->y / other, this->z / other);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::operator-() const noexcept
  {
    return Vector3<T>(-this->x, -this->y, -this->z);
  }

  template<typename T>
  NY_FORCE_INLINE Vector3<T>&
  Vector3<T>::operator+=(const Vector3<T>& other) noexcept
  {
    *this = *this + other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>&
  Vector3<T>::operator-=(const Vector3<T>& other) noexcept
  {
    *this = *this - other;
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE Vector3<T>&
  Vector3<T>::operator+=(T other) noexcept
  {
    *this = *this + other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>&
  Vector3<T>::operator-=(T other) noexcept
  {
    *this = *this - other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>&
  Vector3<T>::operator*=(T other) noexcept
  {
    *this = *this * other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>&
  Vector3<T>::operator/=(T other) noexcept
  {
    *this = *this / other;
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD bool
  Vector3<T>::operator==(const Vector3<T>& other) const noexcept
  {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD bool
  Vector3<T>::operator!=(const Vector3<T>& other) const noexcept
  {
    return !(*this == other);
  }

  template<typename T>
  template<typename U>
  Vector3<T>::operator Vector3<U>() const noexcept
  {
    return Vector3<U>(static_cast<U>(x),
                      static_cast<U>(y),
                      static_cast<U>(z));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T&
  Vector3<T>::operator[](usize index) noexcept
  {
    NY_ASSERT(index < 3);
    return index == 0 ? x : (index == 1 ? y : z);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD const T&
  Vector3<T>::operator[](usize index) const noexcept
  {
    NY_ASSERT(index < 3);
    return index == 0 ? x : (index == 1 ? y : z);
  }
} // namespace nyEngineSDK