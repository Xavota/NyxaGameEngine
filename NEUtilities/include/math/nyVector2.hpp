/******************************************************************************/
/**
 * @file    nyVector2.hpp
 * @author  Dalia Castellanos
 * @date    07/09/2026
 * @brief   Defines the Vector2 class for geometrical operations.
 *
 * A simple 2D vector class for geometrical operations.
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
   * @brief A simple 2D vector class for geometrical operations.
   * @bug No known bugs
   */
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  class NY_API Vector2
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsNumberV<T>,
      "Vector2<T> requires a number type."
    );
#endif

   public:
    /**
     * @brief The default constructor for a Vector2 object, initializing all
     *        components to zero.
     */
    Vector2() noexcept : x(T{ 0 }), y(T{ 0 }) {}
    /**
     * @brief A constructor for a Vector2 object that initializes the vector
     *        with the specified components.
     * @param x The x-component of the vector.
     * @param y The y-component of the vector.
     */
    Vector2(T x, T y) noexcept : x(x), y(y) {}
    /**
     * @brief A constructor for a Vector2 object that initializes the vector
     *        with the specified direction and scale.
     * @param dir   The direction vector.
     * @param scale The scale factor.
     */
    Vector2(const Vector2<T>& dir, T scale) noexcept :
    x(dir.x * scale), y(dir.y * scale) {}

    /**
     * @brief  The dot product of two vectors.
     * @param  other  The other vector for the dot product.
     * @return A new vector with x = x1 * x2, y = y1 * y2.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    dot(const Vector2<T>& other) const noexcept;
    /**
     * @brief  The cross product of two vectors.
     * @param  other  The other vector for the cross product.
     * @return A scalar value representing the signed area of the parallelogram
     *         they span. Positive if the other vector is counter-clockwise from
     *         this vector, negative if clockwise, and zero if they are collinear.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    cross(const Vector2<T>& other) const noexcept;
    /**
     * @brief  Gets a vector perpendicular to this one, rotated 90 degrees
     *         counter-clockwise.
     * @return A new vector that is perpendicular to this vector.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    perpendicular() const noexcept;
    
    /**
     * @brief  The square distance between two points.
     * @param  other  The other point for the distance calculation.
     * @return The square distance between this point and the other point.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    getSqrDistance(const Vector2<T>& other) const noexcept;
    /**
     * @brief  The distance between two points.
     * @param  other  The other point for the distance calculation.
     * @return The distance between this point and the other point.
     */
#if NY_CPP20
    template<FloatingPoint R = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    NY_FORCE_INLINE NY_NODISCARD R
    getDistance(const Vector2<T>& other) const noexcept;
    /**
     * @brief  Returns the square length of the vector in space.
     * @return The square length of the vector.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    getSqrMagnitude() const noexcept;
    /**
     * @brief  Returns the length of the vector in space.
     * @return The length of the vector.
     */
#if NY_CPP20
    template<FloatingPoint R = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    NY_FORCE_INLINE NY_NODISCARD R
    getMagnitude() const noexcept;
    /**
     * @brief  Returns a vector with the same direction as the original but
     *         length of 1 unit.
     * @return The vector normalized.
     */
#if NY_CPP20
    template<FloatingPoint R = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    NY_FORCE_INLINE NY_NODISCARD Vector2<R>
    getNormalized() const noexcept;
    /**
     * @brief  Modifies this vector to have length of 1 unit with its same
     *         direction, and returns it.
     * @return This vector normalized.
     */
    NY_FORCE_INLINE Vector2<T>
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
#if NY_CPP20
    template<FloatingPoint R = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    NY_FORCE_INLINE NY_NODISCARD Vector2<R>
    getTruncated(R newSize) const noexcept;
    /**
     * @brief  Modifies this vector to have the same direction as the original
     *         but with the new size given and returns it.
     * @param  newSize  The desired size of the new vector.
     * @return This vector truncated with the new size.
     */
    NY_FORCE_INLINE Vector2<T>
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
#if NY_CPP20
    template<FloatingPoint R = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector2<R>>
    projection(const Vector2<T>& a, const Vector2<T>& b) noexcept;
    /**
     * @brief  Returns a vector that is the rejection of a over the vector b
     * @param  a  The vector to reject.
     * @param  b  The vector onto which to reject.
     * @return The rejected vector.
     */
#if NY_CPP20
    template<FloatingPoint R = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector2<R>>
    rejection(const Vector2<T>& a, const Vector2<T>& b) noexcept;
    /**
     * @brief  Returns a vector that is the reflection of a with respect to the
     *         normal vector b
     * @param  a  The vector to reflect.
     * @param  b  The normal vector about which to reflect.
     * @return The reflected vector.
     */
#if NY_CPP20
    template<FloatingPoint R = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    static NY_FORCE_INLINE NY_NODISCARD Result<Vector2<R>>
    reflection(const Vector2<T>& a, const Vector2<T>& b) noexcept;

    /**
     * @brief  Linearly interpolates between two vectors based on the given
     *         alpha value.
     * @param  a      The starting vector.
     * @param  b      The ending vector.
     * @param  alpha  The interpolation factor (0.0f to 1.0f).
     * @return The interpolated vector between a and b.
     */
#if NY_CPP20
    template<FloatingPoint Alpha = ConditionalT<IsIntegerV<T>, f32, T>>
#else
    template<typename Alpha = ConditionalT<IsIntegerV<T>, f32, T>>
#endif
    static NY_FORCE_INLINE NY_NODISCARD Vector2<Alpha>
    lerp(const Vector2<T>& a, const Vector2<T>& b, Alpha alpha) noexcept;
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
#if NY_CPP20
    template<FloatingPoint Alpha = ConditionalT<IsIntegerV<T>, f32, T>,
             typename Curve>
#else
    template<typename Alpha = ConditionalT<IsIntegerV<T>, f32, T>,
             typename Curve>
#endif
    static NY_FORCE_INLINE NY_NODISCARD Vector2<Alpha>
    lerp(const Vector2<T>& a, const Vector2<T>& b,
         Alpha alpha, Curve&& curveFunc) noexcept;
    

    /**
     * @brief  Creates and returns a string with the format "{ x:0, y:0 }".
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
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    operator+(const Vector2<T>& other) const noexcept;
    /**
     * @brief  Returns a vector with the subtraction of every component of the
     *         original minus their counterpart on the other vector.
     * @param  other  The other vector for the operation.
     * @return The subtraction of the two vectors.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    operator-(const Vector2<T>& other) const noexcept;

    /**
     * @brief  Returns a vector with the sum of every component of the original
     *         plus the given number.
     * @param  other  The number for the operation.
     * @return The sum of the vector plus the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    operator+(T other) const noexcept;
    /**
     * @brief  Returns a vector with the subtraction of every component of the
     *         original minus the given number.
     * @param  other  The number for the operation.
     * @return The subtraction of the vector minus the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    operator-(T other) const noexcept;
    /**
     * @brief  Returns a vector with the multiplication of every component of the original
     *         by the given number.
     * @param  other  The number for the operation.
     * @return The product of the vector and the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    operator*(T other) const noexcept;
    /**
     * @brief  Returns a vector with the division of every component of the
     *         original by the given number.
     * @param  other  The number for the operation.
     * @return The division of the vector by the number.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    operator/(T other) const noexcept;

    /**
     * @brief  Returns a vector in the opposite direction of the original.
     * @return A vector in the opposite direction of the original.
     */
    NY_FORCE_INLINE NY_NODISCARD Vector2<T>
    operator-() const noexcept;
    
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of itself plus their counterparts of the other vector.
     * @param  other  The other vector to whom is gonna be sum.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector2<T>&
    operator+=(const Vector2<T>& other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of itself minus their counterparts of the other vector.
     * @param  other  The other vector to whom is gonna be subtracted.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector2<T>&
    operator-=(const Vector2<T>& other) noexcept;

    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self plus the number.
     * @param  other  The number to whom is gonna be sum.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector2<T>&
    operator+=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self minus the number.
     * @param  other  The number to whom is gonna be subtracted.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector2<T>&
    operator-=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self times the number.
     * @param  other  The number to whom is gonna be multiplied.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector2<T>&
    operator*=(T other) noexcept;
    /**
     * @brief  Makes every component of the original vector equal to the
     *         components of it self divided by the number.
     * @param  other  The number to whom is gonna be divided.
     * @return This vector after the operation.
     */
    NY_FORCE_INLINE Vector2<T>&
    operator/=(T other) noexcept;
    
    /**
     * @brief  Check if every component of the vector are equal to their
     *         counterpart of the other vector.
     * @param  other  The other vector to check.
     * @return True if they are equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator==(const Vector2<T>& other) const noexcept;
    /**
     * @brief  Check if any component of the vector is not equal to their
     *         counterpart of the other vector.
     * @param  other  The other vector to check.
     * @return True if they are not equal.
     */
    NY_FORCE_INLINE NY_NODISCARD bool
    operator!=(const Vector2<T>& other) const noexcept;

    /**
     * @brief  Converts this vector to a vector of another type.
     * @tparam U The type to which the vector should be converted.
     * @return A new vector of type U with the same components as this vector.
     */
    template<typename U>
    explicit NY_FORCE_INLINE NY_NODISCARD
    operator Vector2<U>() const noexcept;

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
     * @brief A vector with 0 as its components
     */
    static const Vector2 kZERO;
    /*
     * @brief A unitary vector pointing right
     */
    static const Vector2 kRIGHT;
    /*
     * @brief A unitary vector pointing up
     */
    static const Vector2 kUP;
  };

  using Vector2f = Vector2<f32>;
  using Vector2i = Vector2<i32>;
  using Vector2u = Vector2<u32>;

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  inline const Vector2<T> Vector2<T>::kZERO{ T{0}, T{0} };
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  inline const Vector2<T> Vector2<T>::kRIGHT{ T{1}, T{0} };
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  inline const Vector2<T> Vector2<T>::kUP{ T{0}, T{1} };

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD T
  Vector2<T>::dot(const Vector2<T>& other) const noexcept
  {
    T x1 = this->x;
    T y1 = this->y;

    T x2 = other.x;
    T y2 = other.y;

    return x1 * x2 + y1 * y2;
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD T
  Vector2<T>::cross(const Vector2<T>& other) const noexcept
  {
    T x1 = this->x;
    T y1 = this->y;

    T x2 = other.x;
    T y2 = other.y;

    return x1 * y2 - y1 * x2;
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::perpendicular() const noexcept
  {
    return Vector2<T>(-y, x);
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD T
  Vector2<T>::getSqrDistance(const Vector2<T>& other) const noexcept
  {
    T x1 = this->x;
    T y1 = this->y;
    T x2 = other.x;
    T y2 = other.y;

    return Math::sqr(x2 - x1) + Math::sqr(y2 - y1);
  }
#if NY_CPP20
  template<Number T>
  template<FloatingPoint R>
#else
  template<typename T>
  template<typename R>
#endif
  NY_FORCE_INLINE NY_NODISCARD R
  Vector2<T>::getDistance(const Vector2<T>& other) const noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<R>,
      "Vector2<T>::getDistance<R>() requires R to be a floating-point type."
    );
#endif

    auto thisCast = static_cast<Vector2<R>>(*this);
    auto otherCast = static_cast<Vector2<R>>(other);

    return Math::sqrt(thisCast.getSqrDistance(otherCast));
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD T
  Vector2<T>::getSqrMagnitude() const noexcept
  {
    return dot(*this);
  }
#if NY_CPP20
  template<Number T>
  template<FloatingPoint R>
#else
  template<typename T>
  template<typename R>
#endif
  NY_FORCE_INLINE NY_NODISCARD R
  Vector2<T>::getMagnitude() const noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<R>,
      "Vector2<T>::getMagnitude<R>() requires R to be a floating-point type."
    );
#endif

    auto thisCast = static_cast<Vector2<R>>(*this);
    return Math::sqrt(thisCast.getSqrMagnitude());
  }
#if NY_CPP20
  template<Number T>
  template<FloatingPoint R>
#else
  template<typename T>
  template<typename R>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<R>
  Vector2<T>::getNormalized() const noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<R>,
      "Vector2<T>::getNormalized<R>() requires R to be a floating-point type."
    );
#endif

    auto thisCast = static_cast<Vector2<R>>(*this);

    const R magnitude = thisCast.getMagnitude();
    if (magnitude < Math::kTinyFloat<R>)
    {
      return Vector2<R>::kZERO;
    }
    return Vector2<R>(thisCast.x / magnitude, thisCast.y / magnitude);
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>
  Vector2<T>::normalize() noexcept
#if NY_CPP20
  requires FloatingPoint<T>
#endif
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector2<T>::normalize() requires a floating-point type."
    );
#endif

    *this = getNormalized();
    return *this;
  }
#if NY_CPP20
  template<Number T>
  template<FloatingPoint R>
#else
  template<typename T>
  template<typename R>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<R>
  Vector2<T>::getTruncated(R newSize) const noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<R>,
      "Vector2<T>::getTruncated<R>() requires R to be a floating-point type."
    );
#endif

    auto thisCast = static_cast<Vector2<R>>(*this);

    const R magnitude = thisCast.getMagnitude();
    if (magnitude < Math::kTinyFloat<R>)
    {
      return Vector2<R>::kZERO;
    }
    return thisCast * (newSize / magnitude);
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>
  Vector2<T>::truncate(T newSize) noexcept
#if NY_CPP20
  requires FloatingPoint<T>
#endif
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<T>,
      "Vector2<T>::truncate() requires a floating-point type."
    );
#endif

    *this = getTruncated(newSize);
    return *this;
  }

#if NY_CPP20
  template<Number T>
  template<FloatingPoint R>
#else
  template<typename T>
  template<typename R>
#endif
  NY_FORCE_INLINE NY_NODISCARD Result<Vector2<R>>
  Vector2<T>::projection(const Vector2<T>& a, const Vector2<T>& b) noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<R>,
      "Vector2<T>::projection<R>() requires R to be a floating-point type."
    );
#endif

    auto aCast = static_cast<Vector2<R>>(a);
    auto bCast = static_cast<Vector2<R>>(b);

    const R sqrMagnitude = bCast.getSqrMagnitude();
    if (sqrMagnitude < Math::kTinyFloat<R>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Cannot project vector onto zero vector.");
    }
    return bCast * (aCast.dot(bCast) / sqrMagnitude);
  }
#if NY_CPP20
  template<Number T>
  template<FloatingPoint R>
#else
  template<typename T>
  template<typename R>
#endif
  NY_FORCE_INLINE NY_NODISCARD Result<Vector2<R>>
  Vector2<T>::rejection(const Vector2<T>& a, const Vector2<T>& b) noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<R>,
      "Vector2<T>::rejection<R>() requires R to be a floating-point type."
    );
#endif

    auto projResult = projection<R>(a, b);
    if (projResult)
    {
      return static_cast<Vector2<R>>(a) - projResult.value();
    }
    return projResult;
  }
#if NY_CPP20
  template<Number T>
  template<FloatingPoint R>
#else
  template<typename T>
  template<typename R>
#endif
  NY_FORCE_INLINE NY_NODISCARD Result<Vector2<R>>
  Vector2<T>::reflection(const Vector2<T>& a, const Vector2<T>& b) noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<R>,
      "Vector2<T>::reflection<R>() requires R to be a floating-point type."
    );
#endif

    auto aCast = static_cast<Vector2<R>>(a);
    auto bCast = static_cast<Vector2<R>>(b);

    const R sqrMagnitude = bCast.getSqrMagnitude();
    if (sqrMagnitude < Math::kTinyFloat<R>)
    {
      return Status::error(LogLevel::Warning, kModule,
                           "Cannot reflect vector with zero normal.");
    }
    return aCast - (bCast * (R(2) * aCast.dot(bCast) / sqrMagnitude));
  }

#if NY_CPP20
  template<Number T>
  template<FloatingPoint Alpha>
#else
  template<typename T>
  template<typename Alpha>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<Alpha>
  Vector2<T>::lerp(const Vector2<T>& a, const Vector2<T>& b, Alpha alpha) noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Vector2<T>::lerp<Alpha>() requires Alpha to be a floating-point type."
    );
#endif

    Alpha x1 = static_cast<Alpha>(a.x);
    Alpha y1 = static_cast<Alpha>(a.y);
    Alpha x2 = static_cast<Alpha>(b.x);
    Alpha y2 = static_cast<Alpha>(b.y);

    return Vector2<Alpha>(Math::lerp<Alpha>(x1, x2, alpha),
                          Math::lerp<Alpha>(y1, y2, alpha));
  }

#if NY_CPP20
  template<Number T>
  template<FloatingPoint Alpha, typename Curve>
#else
  template<typename T>
  template<typename Alpha, typename Curve>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<Alpha>
  Vector2<T>::lerp(const Vector2<T>& a, const Vector2<T>& b,
                   Alpha alpha, Curve&& curveFunc) noexcept
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsFloatingPointV<Alpha>,
      "Vector2<T>::lerp<Alpha, Curve>() requires Alpha to be a floating-point type."
    );
#endif

    Alpha x1 = static_cast<Alpha>(a.x);
    Alpha y1 = static_cast<Alpha>(a.y);
    Alpha x2 = static_cast<Alpha>(b.x);
    Alpha y2 = static_cast<Alpha>(b.y);

    return Vector2<Alpha>(Math::lerp<Alpha>(x1, x2, alpha, curveFunc),
                          Math::lerp<Alpha>(y1, y2, alpha, curveFunc));
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE String
  Vector2<T>::toString() const noexcept
  {
    return "{ x:" + std::to_string(this->x) +
           ", y:" + std::to_string(this->y) + " }";
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::operator+(const Vector2<T>& other) const noexcept
  {
    return Vector2<T>(this->x + other.x, this->y + other.y);
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::operator-(const Vector2<T>& other) const noexcept
  {
    return Vector2<T>(this->x - other.x, this->y - other.y);
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::operator+(T other) const noexcept
  {
    return Vector2<T>(this->x + other, this->y + other);
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::operator-(T other) const noexcept
  {
    return Vector2<T>(this->x - other, this->y - other);
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::operator*(T other) const noexcept
  {
    return Vector2<T>(this->x * other, this->y * other);
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::operator/(T other) const noexcept
  {
    return Vector2<T>(this->x / other, this->y / other);
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD Vector2<T>
  Vector2<T>::operator-() const noexcept
  {
    return Vector2<T>(-this->x, -this->y);
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>&
  Vector2<T>::operator+=(const Vector2<T>& other) noexcept
  {
    *this = *this + other;
    return *this;
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>&
  Vector2<T>::operator-=(const Vector2<T>& other) noexcept
  {
    *this = *this - other;
    return *this;
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>&
  Vector2<T>::operator+=(T other) noexcept
  {
    *this = *this + other;
    return *this;
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>&
  Vector2<T>::operator-=(T other) noexcept
  {
    *this = *this - other;
    return *this;
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>&
  Vector2<T>::operator*=(T other) noexcept
  {
    *this = *this * other;
    return *this;
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE Vector2<T>&
  Vector2<T>::operator/=(T other) noexcept
  {
    *this = *this / other;
    return *this;
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD bool
  Vector2<T>::operator==(const Vector2<T>& other) const noexcept
  {
    return this->x == other.x && this->y == other.y;
  }
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD bool
  Vector2<T>::operator!=(const Vector2<T>& other) const noexcept
  {
    return !(*this == other);
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  template<typename U>
  Vector2<T>::operator Vector2<U>() const noexcept
  {
    return Vector2<U>(static_cast<U>(x),
                      static_cast<U>(y));
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD T&
  Vector2<T>::operator[](usize index) noexcept
  {
    NY_ASSERT(index < 2);
    return index == 0 ? x : y;
  }

#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  NY_FORCE_INLINE NY_NODISCARD const T&
  Vector2<T>::operator[](usize index) const noexcept
  {
    NY_ASSERT(index < 2);
    return index == 0 ? x : y;
  }
} // namespace nyEngineSDK