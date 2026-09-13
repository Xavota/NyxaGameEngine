/******************************************************************************/
/**
 * @file    nyMatrix2.hpp
 * @author  Dalia Castellanos
 * @date    10/09/2026
 * @brief   Defines the Matrix2 class for numerical operations.
 *
 * A simple 2 by 2 matrix class for numerical operations.
 *
 * @bug	    No known bugs.
 */
 /******************************************************************************/
#pragma once

#include "macros/nyMacros.hpp"
#include "macros/nyUtilitiesApi.hpp"

#include "types/nyConcepts.hpp"
#include "types/nyResult.hpp"

#include "math/nyAngle.h"
#include "math/nyVector2.hpp"

namespace nyEngineSDK
{
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  class NY_API Matrix2
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsNumberV<T>,
      "Matrix2<T> requires a number type."
    );
#endif

   public:
    /**
     * @brief  Constructs a 2x2 matrix with the given array.
     */
    Matrix2(const Array<T, 4>& _m) : m(_m) {}
    /**
     * @brief  Constructs a 2x2 matrix with the given values.
     */
    Matrix2(const T& _m00, const T& _m01, const T& _m10, const T& _m11) :
    m({ _m00, _m01, _m10, _m11 }) {}

    /**
     * @brief  Creates a 2x2 rotation matrix from an angle.
     * @param  angle  The angle in radians.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix2
    fromAngle(const Angle<T>& angle) noexcept;
    /**
     * @brief  Creates a 2x2 matrix from a scale vector.
     * @param  scale  The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix2
    fromScale(const Vector2<T>& scale) noexcept;
    /**
     * @brief  Creates a 2x2 matrix from an angle and a scale vector.
     * @param  angle  The angle in radians.
     * @param  scale  The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix2
    fromAngleScale(const Angle<T>& angle, const Vector2<T>& scale) noexcept;
    /**
     * @brief  Creates a 2x2 matrix from two world axis vectors.
     * @param  axisX  The x-axis vector.
     * @param  axisY  The y-axis vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix2
    fromWorldAxis(const Vector2<T>& axisX, const Vector2<T>& axisY) noexcept;

    /**
     * @brief  Multiplies two matrices and returns the result.
     * @param  a  The first matrix.
     * @param  b  The second matrix.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix2
    multiply(const Matrix2& a, const Matrix2& b) noexcept;

    /**
     * @brief  Multiplies this matrix with another matrix. (this * other)
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2
    multiply(const Matrix2& other) const noexcept;

    /**
     * @brief  Returns the transpose of this matrix.
     * @return The transposed matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2
    getTransposed() const noexcept;
    /**
     * @brief  Transposes this matrix.
     * @return The transposed matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2&
    transpose() noexcept;

    /**
     * @brief  Returns the determinant of this matrix.
     * @return The determinant.
     */
    template<typename R = ConditionalT<IsIntegerV<T>, f32, T>>
    NY_FORCE_INLINE NY_NODISCARD R
    determinant() const noexcept;

    /**
     * @brief  Returns the inverse of this matrix.
     * @return The inverse matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Result<Matrix2>
    getInversed() const noexcept;
    /**
     * @brief  Inverses this matrix.
     * @return The inverse matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Result<Matrix2&>
    invert() const noexcept;

    /**
     * @brief  Adds two matrices and returns the result.
     * @param  other  The matrix to add.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2
    operator+(const Matrix2& other) const noexcept;
    /**
     * @brief  Subtracts two matrices and returns the result.
     * @param  other  The matrix to subtract.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2
    operator-(const Matrix2& other) const noexcept;
    /**
     * @brief  Multiplies two matrices and returns the result.
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2
    operator*(const Matrix2& other) const noexcept;
    /**
     * @brief  Multiplies every value of this matrix with a scalar and returns
     *         the result.
     * @param  other  The scalar to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2
    operator*(const T& scale) const noexcept;

    /**
     * @brief  Adds a matrix to this matrix.
     * @param  other  The matrix to add.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2&
    operator+=(const Matrix2& other) noexcept;
    /**
     * @brief  Subtracts a matrix from this matrix.
     * @param  other  The matrix to subtract.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2&
    operator-=(const Matrix2& other) noexcept;
    /**
     * @brief  Multiplies this matrix with another matrix.
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2&
    operator*=(const Matrix2& other) noexcept;
    /**
     * @brief  Multiplies every value of this matrix with a scalar.
     * @param  other  The scalar to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix2&
    operator*=(const T& scale) noexcept;

   private:
    union
    {
      struct
      {
        T m00, m01;
        T m10, m11;
      };
      Array<T, 4> m;
    };
  };

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::fromAngle(const Angle<T>& angle) noexcept
  {
    return Matrix2(angle.cos(), -angle.sin(),
                   angle.sin(),  angle.cos());
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::fromScale(const Vector2<T>& scale) noexcept
  {
    return Matrix2(scale.x, T(0), T(0), scale.y);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::fromAngleScale(const Angle<T>& angle, const Vector2<T>& scale) noexcept
  {
    return Matrix2(scale.x * angle.cos(), -scale.y * angle.sin(),
                   scale.x * angle.sin(),  scale.y * angle.cos());
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::fromWorldAxis(const Vector2<T>& axisX, const Vector2<T>& axisY) noexcept
  {
    return Matrix2(axisX.x, axisY.x,
                   axisX.y, axisY.y);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::multiply(const Matrix2<T>& a, const Matrix2<T>& b) noexcept
  {
    return Matrix2(a.m00 * b.m00 + a.m01 * b.m10,
                   a.m00 * b.m01 + a.m01 * b.m11,

                   a.m10 * b.m00 + a.m11 * b.m10,
                   a.m10 * b.m01 + a.m11 * b.m11);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::multiply(const Matrix2<T>& other) const noexcept
  {
    return multiply(*this, other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::getTransposed() const noexcept
  {
    return Matrix2(m00, m10, m01, m11);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>&
  Matrix2<T>::transpose() noexcept
  {
    *this = getTransposed();
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Matrix2<T>>
  Matrix2<T>::getInversed() const noexcept
  {
    const T det = determinant();
    if (det < Math::kTinyFloat<R>)
    {
      return Status.error(LogLevel::Warning,
                          "Matrix is singular and cannot be inverted.");
    }
    const T invDet = T(1) / det;
    return Matrix2(m11, -m01, -m10, m00) * invDet;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Matrix2<T>&>
  Matrix2<T>::invert() const noexcept
  {
    *this = getInversed();
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::operator+(const Matrix2<T>& other) const noexcept
  {
    return Matrix2(m00 + other.m00, m01 + other.m01,
                   m10 + other.m10, m11 + other.m11);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::operator-(const Matrix2<T>& other) const noexcept
  {
    return Matrix2(m00 - other.m00, m01 - other.m01,
                   m10 - other.m10, m11 - other.m11);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::operator*(const Matrix2<T>& other) const noexcept
  {
    return multiply(*this, other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::operator*(const T& scale) const noexcept
  {
    return Matrix2(m00 * scale, m01 * scale, m10 * scale, m11 * scale);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>&
  Matrix2<T>::operator+=(const Matrix2<T>& other) noexcept
  {
    *this = *this + other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>&
  Matrix2<T>::operator-=(const Matrix2<T>& other) noexcept
  {
    *this = *this - other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>&
  Matrix2<T>::operator*=(const Matrix2<T>& other) noexcept
  {
    *this = multiply(*this, other);
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>&
  Matrix2<T>::operator*=(const T& scale) noexcept
  {
    *this = *this * scale;
    return *this;
  }

  template<typename T>
  template<typename R>
  NY_FORCE_INLINE NY_NODISCARD R
  Matrix2<T>::determinant() const noexcept
  {
    return static_cast<R>(m00) * static_cast<R>(m11) -
           static_cast<R>(m01) * static_cast<R>(m10);
  }
}