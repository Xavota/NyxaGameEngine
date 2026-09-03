/******************************************************************************/
/**
 * @file    nyMath.hpp
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

#include "macros/nyUtilitiesApi.hpp"
#include "macros/nyMacros.hpp"

#include "types/nyContainers.h"
#include "types/nyTypes.hpp"

#include "math/nyMath.h"

namespace nyEngineSDK
{
  /**
   * @brief A simple 3D vector class for geometrical operations.
   * @bug No known bugs
   */
  template <typename T>
  class NY_API Vector3
  {
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
    NY_FORCE_INLINE NY_NODISCARD float
    dot(const Vector3<T>& other) const noexcept;
    /**
     * @brief  The cross product of two vectors.
     * @param  other  The other vector for the cross product.
     * @return The result of the cross product of the two vectors.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    cross(const Vector3<T>& other) const noexcept;
    
    /**
     * @brief  The distance between two points.
     * @param  other  The other point for the distance calculation.
     * @return The distance between this point and the other point.
     */
    NY_FORCE_INLINE NY_NODISCARD float
    getDistance(const Vector3<T>& other) const noexcept;
    /**
     * @brief  Returns the length of the vector in space.
     * @return The length of the vector.
     */
    NY_FORCE_INLINE NY_NODISCARD float
    getMagnitud() const noexcept;
    /**
     * @brief  Returns a vector with the same direction as the original but
     *         length of 1 unit.
     * @return The vector normalized.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    getNormalized() const noexcept;
    /**
     * @brief  Modifies this vector to have length of 1 unit with its same
     *         direction, and returns it.
     * @return This vector normalized.
     */
    NY_FORCE_INLINE Vector3<T>
    normalize() noexcept;
    /**
     * @brief  Returns a vector with the same direction as the original
     *         but with the new size given.
     * @param  newSize  The desired size of the new vector.
     * @return The vector truncated with the new size.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector3<T>
    getTruncate(float newSize) const noexcept;
    /**
     * @brief  Modifies this vector to have the same direction as the original
     *         but with the new size given and returns it.
     * @param  newSize  The desired size of the new vector.
     * @return This vector truncated with the new size.
     */
    NY_FORCE_INLINE Vector3<T>
    truncate(float newSize) noexcept;
    

    /**
     * @brief  Creates and returns a string with the format "{ x:0, y:0, z:0 }".
     * @return This vector as a String.
     */
    NY_FORCE_INLINE NY_NODISCARD String
    toString() noexcept;

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
     * @brief The components of the vector, in a union so they can be taken
     *        separately or together
     */
    union
    {
      struct
      {
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
      };
      /*
       * @brief All the components of the vector in an array
       */
      Array<T, 3> xyz;
    };

    /*
     * @brief A vector with 0 as its components
     */
    inline static const Vector3 kZERO{ T{0}, T{0}, T{0} };
    /*
     * @brief A unitary vector pointing forward
     */
    inline static const Vector3 kFORWARD{ T{0}, T{0}, T{1} };
    /*
     * @brief A unitary vector pointing right
     */
    inline static const Vector3 kRIGHT{ T{1}, T{0}, T{0} };
    /*
     * @brief A unitary vector pointing up
     */
    inline static const Vector3 kUP{ T{0}, T{1}, T{0} };
  };

  using Vector3f = Vector3<f32>;
  using Vector3i = Vector3<i32>;
  using Vector3u = Vector3<u32>;

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD float
  Vector3<T>::dot(const Vector3<T>& other) const noexcept
  {
    return this->x * other.x + this->y * other.y + this->z * other.z;
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
  NY_FORCE_INLINE NY_NODISCARD float
  Vector3<T>::getDistance(const Vector3<T>& other) const noexcept
  {
    return Math::sqrt(Math::sqr(other.x - this->x) +
                      Math::sqr(other.y - this->y) +
                      Math::sqr(other.z - this->z));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD float
  Vector3<T>::getMagnitud() const noexcept
  {
    return Math::sqrt(Math::sqr(this->x) + Math::sqr(this->y) + Math::sqr(this->z));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::getNormalized() const noexcept
  {
    const float magnitude = getMagnitud();
    if (magnitude == 0.0f)
    {
      return Vector3<T>::kZERO;
    }
    return Vector3<T>(this->x / magnitude, this->y / magnitude, this->z / magnitude);
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>
  Vector3<T>::normalize() noexcept
  {
    *this = getNormalized();
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector3<T>
  Vector3<T>::getTruncate(float newSize) const noexcept
  {
    return getNormalized() * newSize;
  }
  template<typename T>
  NY_FORCE_INLINE Vector3<T>
  Vector3<T>::truncate(float newSize) noexcept
  {
    *this = getTruncate(newSize);
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE String
  Vector3<T>::toString() noexcept
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
} // namespace nyEngineSDK