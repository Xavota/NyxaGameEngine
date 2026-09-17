/******************************************************************************/
/**
 * @file    nyVector4.hpp
 * @author  Dalia Castellanos
 * @date    02/09/2026
 * @brief   Defines the Vector4 class for geometrical operations.
 *
 * A simple 4D vector class for geometrical operations.
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
   * @brief A simple 4D vector class for geometrical operations.
   * @bug No known bugs
   */
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  class NY_API Vector4
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsNumberV<T>,
      "Vector4<T> requires a number type."
    );
#endif

   public:
    /**
     * @brief The default constructor for a Vector4 object, initializing all
     *        components to zero.
     */
    Vector4() noexcept : x(T{ 0 }), y(T{ 0 }), z(T{ 0 }), w(T{ 0 }) {}
    /**
     * @brief A constructor for a Vector4 object that initializes the vector
     *        with the specified components.
     * @param x The x-component of the vector.
     * @param y The y-component of the vector.
     * @param z The z-component of the vector.
     * @param w The w-component of the vector.
     */
    Vector4(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}
    /**
     * @brief A constructor for a Vector4 object that initializes the vector
     *        with the specified direction and scale.
     * @param dir   The direction vector.
     * @param scale The scale factor.
     */
    Vector4(const Vector4<T>& dir, T scale) noexcept :
    x(dir.x * scale), y(dir.y * scale), z(dir.z * scale), w(dir.w * scale) {}

    /**
     * @brief  The dot product of two vectors.
     * @param  other  The other vector for the dot product.
     * @return A new vector with
     *         x = x1 * x2, y = y1 * y2, z = z1 * z2, w = w1 * w2.
     */
    template<typename R = T>
    NY_FORCE_INLINE NY_NODISCARD R
    dot(const Vector4<T>& other) const noexcept;
    
    /**
     * @brief  The square distance between two points.
     * @param  other  The other point for the distance calculation.
     * @return The square distance between this point and the other point.
     */
    template<typename R = T>
    NY_FORCE_INLINE NY_NODISCARD R
    getSqrDistance(const Vector4<T>& other) const noexcept;
    /**
     * @brief  The distance between two points.
     * @param  other  The other point for the distance calculation.
     * @return The distance between this point and the other point.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    NY_FORCE_INLINE NY_NODISCARD R
    getDistance(const Vector4<T>& other) const noexcept;
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
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
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
    NY_FORCE_INLINE Vector4<T>
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
    NY_FORCE_INLINE NY_NODISCARD Vector4<R>
    getTruncated(R newSize) const noexcept;
    /**
     * @brief  Modifies this vector to have the same direction as the original
     *         but with the new size given and returns it.
     * @param  newSize  The desired size of the new vector.
     * @return This vector truncated with the new size.
     */
    NY_FORCE_INLINE Vector4<T>
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
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector4<R>>
    projection(const Vector4<T>& a, const Vector4<T>& b) noexcept;
    /**
     * @brief  Returns a vector that is the rejection of a over the vector b
     * @param  a  The vector to reject.
     * @param  b  The vector onto which to reject.
     * @return The rejected vector.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector4<R>>
    rejection(const Vector4<T>& a, const Vector4<T>& b) noexcept;
    /**
     * @brief  Returns a vector that is the reflection of a with respect to the
     *         normal vector b
     * @param  a  The vector to reflect.
     * @param  b  The normal vector about which to reflect.
     * @return The reflected vector.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector4<R>>
    reflection(const Vector4<T>& a, const Vector4<T>& b) noexcept;

    /**
     * @brief  Linearly interpolates between two vectors based on the given
     *         alpha value.
     * @param  a      The starting vector.
     * @param  b      The ending vector.
     * @param  alpha  The interpolation factor (0.0f to 1.0f).
     * @return The interpolated vector between a and b.
     */
    template<typename Alpha = ConditionalT<IsIntegerV<T>, f32, T>>
    static NY_FORCE_INLINE NY_NODISCARD Vector4<Alpha>
    lerp(const Vector4<T>& a, const Vector4<T>& b, Alpha alpha) noexcept;
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
    static NY_FORCE_INLINE NY_NODISCARD Vector4<Alpha>
    lerp(const Vector4<T>& a, const Vector4<T>& b,
         Alpha alpha, Curve&& curveFunc) noexcept;

    /**
     * @brief  Returns a vector with every component divided by the w component.
     * @return The homogenized vector.
     */
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector4<T>>
    getHomogenized() noexcept;
    /**
     * @brief  Modifies this vector to have every component divided by the w
     *         component and returns it.
     * @return This vector homogenized.
     */
    static NY_FORCE_INLINE Result<Vector4<T>>
    homogenize() noexcept;
    

    /**
     * @brief  Creates and returns a string with the format
     *         "{ x:0, y:0, z:0, w:0 }".
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
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
    operator+(const Vector4<T>& other) const noexcept;
    /**
     * @brief  Returns a vector with the subtraction of every component of the
     *         original minus their counterpart on the other vector.
     * @param  other  The other vector for the operation.
     * @return The subtraction of the two vectors.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
    operator-(const Vector4<T>& other) const noexcept;

    /**
     * @brief  Returns a vector with the sum of every component of the original
     *         plus the given number.
     * @param  other  The number for the operation.
     * @return The sum of the vector plus the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
    operator+(T other) const noexcept;
    /**
     * @brief  Returns a vector with the subtraction of every component of the
     *         original minus the given number.
     * @param  other  The number for the operation.
     * @return The subtraction of the vector minus the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
    operator-(T other) const noexcept;
    /**
     * @brief  Returns a vector with the multiplication of every component of the original
     *         by the given number.
     * @param  other  The number for the operation.
     * @return The product of the vector and the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
    operator*(T other) const noexcept;
    /**
     * @brief  Returns a vector with the division of every component of the
     *         original by the given number.
     * @param  other  The number for the operation.
     * @return The division of the vector by the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
    operator/(T other) const noexcept;

    /**
     * @brief  Returns a vector in the opposite direction of the original.
     * @return A vector in the opposite direction of the original.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector4<T>
    operator-() const noexcept;
    
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of itself plus their counterparts of the other vector.
     * @param  other  The other vector to whom is gonna be sum.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector4<T>&
    operator+=(const Vector4<T>& other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of itself minus their counterparts of the other vector.
     * @param  other  The other vector to whom is gonna be subtracted.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector4<T>&
    operator-=(const Vector4<T>& other) noexcept;

    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self plus the number.
     * @param  other  The number to whom is gonna be sum.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector4<T>&
    operator+=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self minus the number.
     * @param  other  The number to whom is gonna be subtracted.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector4<T>&
    operator-=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self times the number.
     * @param  other  The number to whom is gonna be multiplied.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector4<T>&
    operator*=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self divided by the number.
     * @param  other  The number to whom is gonna be divided.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector4<T>&
    operator/=(T other) noexcept;
    
    /**
     * @brief  Check if every component of the vector are equal to their
     *         counterpart of the other vector.
     * @param  other  The other vector to check.
     * @return True if they are equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator==(const Vector4<T>& other) const noexcept;
    /**
     * @brief  Check if any component of the vector is not equal to their
     *         counterpart of the other vector.
     * @param  other  The other vector to check.
     * @return True if they are not equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator!=(const Vector4<T>& other) const noexcept;

    /**
     * @brief  Converts this vector to a vector of another type.
     * @tparam U The type to which the vector should be converted.
     * @return A new vector of type U with the same components as this vector.
     */
    template<typename U>
    explicit NY_FORCE_INLINE NY_NODISCARD
    operator Vector4<U>() const noexcept;

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
     * @brief The w component of the vector
     */
    T w;

    /*
     * @brief A vector with 0 as its components
     */
    static const Vector4 kZERO;
    /*
     * @brief A unitary vector pointing forward
     */
    static const Vector4 kFORWARD;
    /*
     * @brief A unitary vector pointing right
     */
    static const Vector4 kRIGHT;
    /*
     * @brief A unitary vector pointing up
     */
    static const Vector4 kUP;
    /*
     * @brief A zero vector with w component equal to 1
     */
    static const Vector4 kW;
  };

  using Vector4f = Vector4<f32>;
  using Vector4i = Vector4<i32>;
  using Vector4u = Vector4<u32>;

  template<typename T>
  inline const Vector4<T> Vector4<T>::kZERO{ T{0}, T{0}, T{0}, T{0} };
  template<typename T>
  inline const Vector4<T> Vector4<T>::kFORWARD{ T{0}, T{0}, T{1}, T{0} };
  template<typename T>
  inline const Vector4<T> Vector4<T>::kRIGHT{ T{1}, T{0}, T{0}, T{0} };
  template<typename T>
  inline const Vector4<T> Vector4<T>::kUP{ T{0}, T{1}, T{0}, T{0} };
  template<typename T>
  inline const Vector4<T> Vector4<T>::kW{ T{0}, T{0}, T{0}, T{1} };

  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector4<T>::dot(const Vector4<T>& other) const noexcept
  {
    R x1 = static_cast<R>(this->x);
    R y1 = static_cast<R>(this->y);
    R z1 = static_cast<R>(this->z);
    R w1 = static_cast<R>(this->w);

    R x2 = static_cast<R>(other.x);
    R y2 = static_cast<R>(other.y);
    R z2 = static_cast<R>(other.z);
    R w2 = static_cast<R>(other.w);

    return x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;
  }

  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector4<T>::getSqrDistance(const Vector4<T>& other) const noexcept
  {
    R x1 = static_cast<R>(this->x);
    R y1 = static_cast<R>(this->y);
    R z1 = static_cast<R>(this->z);
    R w1 = static_cast<R>(this->w);

    R x2 = static_cast<R>(other.x);
    R y2 = static_cast<R>(other.y);
    R z2 = static_cast<R>(other.z);
    R w2 = static_cast<R>(other.w);

    return Math::sqr<R>(x2 - x1) + Math::sqr<R>(y2 - y1) +
           Math::sqr<R>(z2 - z1) + Math::sqr<R>(w2 - w1);
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector4<T>::getDistance(const Vector4<T>& other) const noexcept
  {
    return Math::sqrt<R>(getSqrDistance<R>(other));
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector4<T>::getSqrMagnitude() const noexcept
  {
    return dot<R>(*this);
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Vector4<T>::getMagnitude() const noexcept
  {
    return Math::sqrt<R>(getSqrMagnitude<R>());
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::getNormalized() const noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector4<T>::getNormalized() requires a floating-point type."
    );
#endif

    const T magnitude = getMagnitude();
    if (magnitude < Math::kTinyFloat<T>)
    {
      return Vector4<T>::kZERO;
    }
    return Vector4<T>(this->x / magnitude, this->y / magnitude,
                      this->z / magnitude, this->w / magnitude);
  }
  template<typename T>
  NY_FORCE_INLINE Vector4<T>
  Vector4<T>::normalize() noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector4<T>::normalize() requires a floating-point type."
    );
#endif

    *this = getNormalized();
    return *this;
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Vector4<R>
  Vector4<T>::getTruncated(R newSize) const noexcept
  {
    const R magnitude = getMagnitude<R>();
    if (magnitude < Math::kTinyFloat<R>)
    {
      return Vector4<R>::kZERO;
    }
    return static_cast<Vector4<R>>(*this) * (newSize / magnitude);
  }
  template<typename T>
  NY_FORCE_INLINE Vector4<T>
  Vector4<T>::truncate(T newSize) noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector4<T>::truncate() requires a floating-point type."
    );
#endif

    *this = getTruncated(newSize);
    return *this;
  }

  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector4<R>>
  Vector4<T>::projection(const Vector4<T>& a, const Vector4<T>& b) noexcept
  {
    const R sqrMagnitude = b.getSqrMagnitude<R>();
    if (sqrMagnitude < Math::kTinyFloat<R>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Cannot project vector onto zero vector.");
    }
    auto aCast = static_cast<Vector4<R>>(a);
    auto bCast = static_cast<Vector4<R>>(b);
    return bCast * (aCast.dot(bCast) / sqrMagnitude);
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector4<R>>
  Vector4<T>::rejection(const Vector4<T>& a, const Vector4<T>& b) noexcept
  {
    auto projResult = projection<R>(a, b);
    if (projResult)
    {
      return static_cast<Vector4<R>>(a) - projResult.value();
    }
    return projResult;
  }
  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector4<R>>
  Vector4<T>::reflection(const Vector4<T>& a, const Vector4<T>& b) noexcept
  {
    const R sqrMagnitude = b.getSqrMagnitude<R>();
    if (sqrMagnitude < Math::kTinyFloat<R>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Cannot reflect vector with zero normal.");
    }
    auto aCast = static_cast<Vector4<R>>(a);
    auto bCast = static_cast<Vector4<R>>(b);
    return aCast - (bCast * (R(2) * aCast.dot(bCast) / sqrMagnitude));
  }

  template<typename T>
  template<typename Alpha>
  NY_FORCE_INLINE NY_NODISCARD Vector4<Alpha>
  Vector4<T>::lerp(const Vector4<T>& a, const Vector4<T>& b, Alpha alpha) noexcept
  {
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Alpha must be a floating-point type."
    );

    Alpha x1 = static_cast<Alpha>(a.x);
    Alpha y1 = static_cast<Alpha>(a.y);
    Alpha z1 = static_cast<Alpha>(a.z);
    Alpha w1 = static_cast<Alpha>(a.w);

    Alpha x2 = static_cast<Alpha>(b.x);
    Alpha y2 = static_cast<Alpha>(b.y);
    Alpha z2 = static_cast<Alpha>(b.z);
    Alpha w2 = static_cast<Alpha>(b.w);

    return Vector4<Alpha>(Math::lerp<Alpha>(x1, x2, alpha),
                          Math::lerp<Alpha>(y1, y2, alpha),
                          Math::lerp<Alpha>(z1, z2, alpha),
                          Math::lerp<Alpha>(w1, w2, alpha));
  }
  template<typename T>
  template<typename Alpha, typename Curve>
  NY_FORCE_INLINE NY_NODISCARD Vector4<Alpha>
  Vector4<T>::lerp(const Vector4<T>& a, const Vector4<T>& b,
                   Alpha alpha, Curve&& curveFunc) noexcept
  {
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Alpha must be a floating-point type."
    );

    Alpha x1 = static_cast<Alpha>(a.x);
    Alpha y1 = static_cast<Alpha>(a.y);
    Alpha z1 = static_cast<Alpha>(a.z);
    Alpha w1 = static_cast<Alpha>(a.w);

    Alpha x2 = static_cast<Alpha>(b.x);
    Alpha y2 = static_cast<Alpha>(b.y);
    Alpha z2 = static_cast<Alpha>(b.z);
    Alpha w2 = static_cast<Alpha>(b.w);

    return Vector4<Alpha>(Math::lerp<Alpha>(x1, x2, alpha, curveFunc),
                          Math::lerp<Alpha>(y1, y2, alpha, curveFunc),
                          Math::lerp<Alpha>(z1, z2, alpha, curveFunc),
                          Math::lerp<Alpha>(w1, w2, alpha, curveFunc));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector4<T>>
  Vector4<T>::getHomogenized() noexcept
  {
    if (Math::abs(this->w) < Math::kTinyFloat<T>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Cannot homogenize vector with w near zero.");
    }

    return Vector4<T>(this->x / this->w, this->y / this->w,
                      this->z / this->w, 1.0f);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Vector4<T>>
  Vector4<T>::homogenize() noexcept
  {
    auto result = getHomogenized();
    if (result)
    {
      *this = result.value();
    }
    return result;
  }

  template<typename T>
  NY_FORCE_INLINE String
  Vector4<T>::toString() const noexcept
  {
    return "{ x:" + std::to_string(this->x) +
           ", y:" + std::to_string(this->y) +
           ", z:" + std::to_string(this->z) + 
           ", w:" + std::to_string(this->w) + " }";
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::operator+(const Vector4<T>& other) const noexcept
  {
    return Vector4<T>(this->x + other.x, this->y + other.y,
                      this->z + other.z, this->w + other.w);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::operator-(const Vector4<T>& other) const noexcept
  {
    return Vector4<T>(this->x - other.x, this->y - other.y,
                      this->z - other.z, this->w - other.w);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::operator+(T other) const noexcept
  {
    return Vector4<T>(this->x + other, this->y + other,
                      this->z + other, this->w + other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::operator-(T other) const noexcept
  {
    return Vector4<T>(this->x - other, this->y - other,
                      this->z - other, this->w - other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::operator*(T other) const noexcept
  {
    return Vector4<T>(this->x * other, this->y * other,
                      this->z * other, this->w * other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::operator/(T other) const noexcept
  {
    return Vector4<T>(this->x / other, this->y / other,
                      this->z / other, this->w / other);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Vector4<T>
  Vector4<T>::operator-() const noexcept
  {
    return Vector4<T>(-this->x, -this->y, -this->z, -this->w);
  }

  template<typename T>
  NY_FORCE_INLINE Vector4<T>&
  Vector4<T>::operator+=(const Vector4<T>& other) noexcept
  {
    *this = *this + other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector4<T>&
  Vector4<T>::operator-=(const Vector4<T>& other) noexcept
  {
    *this = *this - other;
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE Vector4<T>&
  Vector4<T>::operator+=(T other) noexcept
  {
    *this = *this + other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector4<T>&
  Vector4<T>::operator-=(T other) noexcept
  {
    *this = *this - other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector4<T>&
  Vector4<T>::operator*=(T other) noexcept
  {
    *this = *this * other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE Vector4<T>&
  Vector4<T>::operator/=(T other) noexcept
  {
    *this = *this / other;
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD bool
  Vector4<T>::operator==(const Vector4<T>& other) const noexcept
  {
    return this->x == other.x && this->y == other.y &&
           this->z == other.z && this->w == other.w;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD bool
  Vector4<T>::operator!=(const Vector4<T>& other) const noexcept
  {
    return !(*this == other);
  }

  template<typename T>
  template<typename U>
  Vector4<T>::operator Vector4<U>() const noexcept
  {
    return Vector4<U>(static_cast<U>(x),
                      static_cast<U>(y),
                      static_cast<U>(z),
                      static_cast<U>(w));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T&
  Vector4<T>::operator[](usize index) noexcept
  {
    NY_ASSERT(index < 4);
    return index == 0 ? x : (index == 1 ? y : (index == 2 ? z : w));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD const T&
  Vector4<T>::operator[](usize index) const noexcept
  {
    NY_ASSERT(index < 4);
    return index == 0 ? x : (index == 1 ? y : (index == 2 ? z : w));
  }
} // namespace nyEngineSDK