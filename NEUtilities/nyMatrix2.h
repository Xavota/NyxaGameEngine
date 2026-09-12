#pragma once

#include "macros/nyMacros.hpp"
#include "macros/nyUtilitiesApi.hpp"

#include "types/nyContainers.hpp"
#include "types/nyResult.hpp"
#include "types/nyStatus.hpp"

#include "math/nyVector2.hpp"

namespace nyEngineSDK
{
  template<typename T>
  class NY_API Matrix2
  {
   public:
    /**
     * @brief  Constructs a 2x2 matrix with the given array.
     */
    Matrix2(Array<T, 4> _m) : m(_m) {}
    /**
     * @brief  Constructs a 2x2 matrix with the given values.
     */
    Matrix2(const T& _m00, const T& _m01, const T& _m10, const T& _m11) :
    m({ _m00, _m01, _m10, _m11 }) {}
    /**
     * @brief  Constructs a 2x2 matrix with the axis vectors.
     */
    Matrix2(const Vector2<T>& _axisx, const Vector2<T>& _axisy) :
    m({ _axisx.x, _axisy.x, _axisx.y, _axisy.y }) {}
    
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
    template<typename R = std::conditional_t<std::is_integral_v<T>, f32, T>>
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
  Matrix2<T>::multiply(const Matrix2<T>& a, const Matrix2<T>& b) noexcept
  {
    return Matrix2(a.m[0] * b.m[0] + a.m[1] * b.m[2], a.m[0] * b.m[1] + a.m[1] * b.m[3],
                   a.m[2] * b.m[0] + a.m[3] * b.m[2], a.m[2] * b.m[1] + a.m[3] * b.m[3]);
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
      return Status.error(LogLevel::Warning, "Matrix is singular and cannot be inverted.");
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
    return Matrix2(m00 + other.m00, m01 + other.m01, m10 + other.m10, m11 + other.m11);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix2<T>
  Matrix2<T>::operator-(const Matrix2<T>& other) const noexcept
  {
    return Matrix2(m00 - other.m00, m01 - other.m01, m10 - other.m10, m11 - other.m11);
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
    return R(m00 * m11 - m01 * m10);
  }
}