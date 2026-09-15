/******************************************************************************/
/**
 * @file    nyMatrix3.hpp
 * @author  Dalia Castellanos
 * @date    12/09/2026
 * @brief   Defines the Matrix3 class for numerical operations.
 *
 * A simple 3 by 3 matrix class for numerical operations.
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
#include "math/nyVector3.hpp"

namespace nyEngineSDK
{
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  class NY_API Matrix3
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsNumberV<T>,
      "Matrix3<T> requires a number type."
    );
#endif

   public:
    /**
     * @brief  Constructs a 3x3 matrix with the given array.
     */
    Matrix3(const Array<T, 9>& _m) : m(_m) {}
    /**
     * @brief  Constructs a 3x3 matrix with the given values.
     */
    Matrix3(const T& _m00, const T& _m01, const T& _m02,
            const T& _m10, const T& _m11, const T& _m12,
            const T& _m20, const T& _m21, const T& _m22) :
    m({ _m00, _m01, _m02,
        _m10, _m11, _m12,
        _m20, _m21, _m22 }) {}

    /**
     * @brief  Creates a 2D rotation matrix from an angle with the last values
               on each column set to zero and the last row set to (0, 0, 1).
               Used for 2D transformations with translations.
     * @param  angle  The angle in radians.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromAngle2D(const Angle<T>& angle) noexcept;
    /**
     * @brief  Creates a 2D scale matrix from a scale 2D vector with the last
     *         values on each column set to zero and the last row set to (0, 0, 1).
               Used for 2D transformations with translations.
     * @param  scale  The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromScale2D(const Vector2<T>& scale) noexcept;
    /**
     * @brief  Creates a 2D translation matrix from a translation 2D vector.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromTranslation2D(const Vector2<T>& translation) noexcept;
    /**
     * @brief  Creates a 2D transformation matrix from an angle and a
     *         2D scale vector.
     * @param  angle  The angle in radians.
     * @param  scale  The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromAngleScale2D(const Angle<T>& angle, const Vector2<T>& scale) noexcept;
    /**
     * @brief  Creates a 2D transformation matrix from an angle and a
     *         translation 2D vector.
     * @param  angle        The angle in radians.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromAngleTranslation2D(const Angle<T>& angle,
                           const Vector2<T>& translation) noexcept;
    /**
     * @brief  Creates a 2D transformation matrix from a scale 2D vector and
     *         a translation 2D vector.
     * @param  scale        The scale vector.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromScaleTranslation2D(const Vector2<T>& scale,
                           const Vector2<T>& translation) noexcept;
    /**
     * @brief  Creates a 2D transformation matrix from an angle,
     *         a scale 2D vector and a translation 2D vector.
     * @param  angle        The angle in radians.
     * @param  scale        The scale vector.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromAngleScaleTranslation2D(const Angle<T>& angle,
                                const Vector2<T>& scale,
                                const Vector2<T>& translation) noexcept;

    /**
     * @brief  Creates a 3D rotation matrix from Euler angles.
     * @param  angles  The Euler angles.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromAngle3D(const EulerAngles<T>& angles) noexcept;
    /**
     * @brief  Creates a 3D scale matrix from a scale 3D vector.
     * @param  scale  The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromScale3D(const Vector3<T>& scale) noexcept;
    /**
     * @brief  Creates a 3D transformation matrix from Euler angles and a
     *         3D scale vector.
     * @param  angles  The Euler angles.
     * @param  scale   The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromAngleScale3D(const EulerAngles<T>& angles, const Vector3<T>& scale) noexcept;

    /**
     * @brief  Creates a 3x3 matrix from three world axis vectors.
     * @param  axisX  The x-axis vector.
     * @param  axisY  The y-axis vector.
     * @param  axisZ  The z-axis vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    fromWorldAxis(const Vector3<T>& axisX,
                  const Vector3<T>& axisY,
                  const Vector3<T>& axisZ) noexcept;

    /**
     * @brief  Multiplies two matrices and returns the result.
     * @param  a  The first matrix.
     * @param  b  The second matrix.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix3
    multiply(const Matrix3& a, const Matrix3& b) noexcept;

    /**
     * @brief  Multiplies this matrix with another matrix. (this * other)
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    multiply(const Matrix3& other) const noexcept;

    /**
     * @brief  Returns the transpose of this matrix.
     * @return The transposed matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    getTransposed() const noexcept;
    /**
     * @brief  Transposes this matrix.
     * @return The transposed matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3&
    transpose() noexcept;

    /**
     * @brief  Returns the cofactor matrix of this matrix.
     * @return The cofactor matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    getCofactor() const noexcept;

    /**
     * @brief  Returns the adjoint matrix of this matrix.
     * @return The adjoint matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    getAdjoint() const noexcept;

    /**
     * @brief  Returns the determinant of this matrix.
     * @return The determinant.
     */
    NY_FORCE_INLINE NY_NODISCARD T
    determinant() const noexcept;

    /**
     * @brief  Returns the inverse of this matrix.
     * @return The inverse matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Result<Matrix3>
    getInversed() const noexcept;
    /**
     * @brief  Inverses this matrix.
     * @return The inverse matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Result<Matrix3&>
    invert() const noexcept;

    /**
     * @brief  Adds two matrices and returns the result.
     * @param  other  The matrix to add.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    operator+(const Matrix3& other) const noexcept;
    /**
     * @brief  Subtracts two matrices and returns the result.
     * @param  other  The matrix to subtract.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    operator-(const Matrix3& other) const noexcept;
    /**
     * @brief  Multiplies two matrices and returns the result.
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    operator*(const Matrix3& other) const noexcept;
    /**
     * @brief  Multiplies every value of this matrix with a scalar and returns
     *         the result.
     * @param  other  The scalar to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3
    operator*(const T& scale) const noexcept;

    /**
     * @brief  Adds a matrix to this matrix.
     * @param  other  The matrix to add.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3&
    operator+=(const Matrix3& other) noexcept;
    /**
     * @brief  Subtracts a matrix from this matrix.
     * @param  other  The matrix to subtract.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3&
    operator-=(const Matrix3& other) noexcept;
    /**
     * @brief  Multiplies this matrix with another matrix.
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3&
    operator*=(const Matrix3& other) noexcept;
    /**
     * @brief  Multiplies every value of this matrix with a scalar.
     * @param  other  The scalar to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix3&
    operator*=(const T& scale) noexcept;

   private:
    union
    {
      struct
      {
        T m00, m01, m02;
        T m10, m11, m12;
        T m20, m21, m22;
      };
      Array<T, 9> m;
    };
  };

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromAngle2D(const Angle<T>& angle) noexcept
  {
    return Matrix3(angle.cos(), -angle.sin(), T(0),
                   angle.sin(),  angle.cos(), T(0),
                          T(0),         T(0), T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromScale2D(const Vector2<T>& scale) noexcept
  {
    return Matrix3(scale.x,    T(0), T(0),
                      T(0), scale.y, T(0),
                      T(0),    T(0), T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromTranslation2D(const Vector2<T>& translation) noexcept
  {
    return Matrix3(T(1), T(0), translation.x,
                   T(0), T(1), translation.y,
                   T(0), T(0),          T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromAngleScale2D(const Angle<T>& angle,
                               const Vector2<T>& scale) noexcept
  {
    return Matrix3(scale.x * angle.cos(), -scale.y * angle.sin(), T(0),
                   scale.x * angle.sin(),  scale.y * angle.cos(), T(0),
                                    T(0),                   T(0), T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromAngleTranslation2D(const Angle<T>& angle,
                                     const Vector2<T>& translation) noexcept
  {
    return Matrix3(angle.cos(), -angle.sin(), translation.x,
                   angle.sin(),  angle.cos(), translation.y,
                          T(0),         T(0),          T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromScaleTranslation2D(const Vector2<T>& scale,
                                     const Vector2<T>& translation) noexcept
  {
    return Matrix3(scale.x,    T(0), translation.x,
                      T(0), scale.y, translation.y,
                      T(0),    T(0),          T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromAngleScaleTranslation2D(const Angle<T>& angle,
                                          const Vector2<T>& scale,
                                          const Vector2<T>& translation) noexcept
  {
    return Matrix3(scale.x * angle.cos(), -scale.y * angle.sin(), translation.x,
                   scale.x * angle.sin(),  scale.y * angle.cos(), translation.y,
                                    T(0),                   T(0),          T(1));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromAngle3D(const EulerAngles<T>& angles) noexcept
  {
    Matrix3<T> rotationX(T(1),               T(0),                T(0),
                         T(0), angles.pitch.cos(), -angles.pitch.sin(),
                         T(0), angles.pitch.sin(),  angles.pitch.cos());
    Matrix3<T> rotationY( angles.pitch.cos(), T(0), angles.pitch.sin(),
                                        T(0), T(1),               T(0),
                         -angles.pitch.sin(), T(0), angles.pitch.cos());
    Matrix3<T> rotationZ(angles.pitch.cos(), -angles.pitch.sin(), T(0),
                         angles.pitch.sin(),  angles.pitch.cos(), T(0),
                                       T(0),                T(0), T(1));
    // TODO: EVENTUALLY THIS ORDER SHOULD BE CHANGED AT RUNTIME WITH USER PREFERENCES
    return rotationZ * rotationX * rotationY;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromScale3D(const Vector3<T>& scale) noexcept
  {
    return Matrix3(scale.x,    T(0),    T(0),
                      T(0), scale.y,    T(0),
                      T(0),    T(0), scale.z);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromAngleScale3D(const EulerAngles<T>& angles,
                               const Vector3<T>& scale) noexcept
  {
    Matrix3<T> rotationMat = Matrix3<T>::fromAngle3D(angles);
    Matrix3<T> scaleMat = Matrix3<T>::fromScale3D(scale);
    return rotationMat * scaleMat;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::fromWorldAxis(const Vector3<T>& axisX,
                            const Vector3<T>& axisY,
                            const Vector3<T>& axisZ) noexcept
  {
    return Matrix3(axisX.x, axisY.x, axisZ.x,
                   axisX.y, axisY.y, axisZ.y,
                   axisX.z, axisY.z, axisZ.z);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::multiply(const Matrix3<T>& a, const Matrix3<T>& b) noexcept
  {
    return Matrix3(a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20,
                   a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21,
                   a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,

                   a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20,
                   a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21,
                   a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,

                   a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20,
                   a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21,
                   a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::multiply(const Matrix3<T>& other) const noexcept
  {
    return multiply(*this, other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::getTransposed() const noexcept
  {
    return Matrix3(m00, m10, m20,
                   m01, m11, m21,
                   m02, m12, m22);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>&
  Matrix3<T>::transpose() noexcept
  {
    *this = getTransposed();
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::getCofactor() const noexcept
  {
    T c00 = Matrix2<T>(m11, m12,
                       m21, m22).determinant();
    T c01 = Matrix2<T>(m10, m12,
                       m20, m22).determinant();
    T c02 = Matrix2<T>(m10, m11,
                       m20, m21).determinant();

    T c10 = Matrix2<T>(m01, m02,
                       m21, m22).determinant();
    T c11 = Matrix2<T>(m00, m02,
                       m20, m22).determinant();
    T c12 = Matrix2<T>(m00, m01,
                       m20, m21).determinant();

    T c20 = Matrix2<T>(m01, m02,
                       m11, m12).determinant();
    T c21 = Matrix2<T>(m00, m02,
                       m10, m12).determinant();
    T c22 = Matrix2<T>(m00, m01,
                       m10, m11).determinant();

    return Matrix3( c00, -c01,  c02,
                   -c10,  c11, -c12,
                    c20, -c21,  c22);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::getAdjoint() const noexcept
  {
    return getCofactor().getTransposed();
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Matrix3<T>::determinant() const noexcept
  {
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 -
           m02 * m11 * m20 - m00 * m12 * m21 - m01 * m10 * m22;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Matrix3<T>>
  Matrix3<T>::getInversed() const noexcept
  {
    const T det = determinant();
    if (det < Math::kTinyFloat<R>)
    {
      return Status.error(LogLevel::Warning,
                          "Matrix is singular and cannot be inverted.");
    }
    const T invDet = T(1) / det;
    return getAdjoint() * invDet;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Matrix3<T>&>
  Matrix3<T>::invert() const noexcept
  {
    *this = getInversed();
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::operator+(const Matrix3<T>& other) const noexcept
  {
    return Matrix3(m00 + other.m00, m01 + other.m01, m02 + other.m02,
                   m10 + other.m10, m11 + other.m11, m12 + other.m12,
                   m20 + other.m20, m21 + other.m21, m22 + other.m22);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::operator-(const Matrix3<T>& other) const noexcept
  {
    return Matrix3(m00 - other.m00, m01 - other.m01, m02 - other.m02,
                   m10 - other.m10, m11 - other.m11, m12 - other.m12,
                   m20 - other.m20, m21 - other.m21, m22 - other.m22);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::operator*(const Matrix3<T>& other) const noexcept
  {
    return multiply(*this, other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>
  Matrix3<T>::operator*(const T& scale) const noexcept
  {
    return Matrix3(m00 * scale, m01 * scale, m02 * scale,
                   m10 * scale, m11 * scale, m12 * scale,
                   m20 * scale, m21 * scale, m22 * scale);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>&
  Matrix3<T>::operator+=(const Matrix3<T>& other) noexcept
  {
    *this = *this + other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>&
  Matrix3<T>::operator-=(const Matrix3<T>& other) noexcept
  {
    *this = *this - other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>&
  Matrix3<T>::operator*=(const Matrix3<T>& other) noexcept
  {
    *this = multiply(*this, other);
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix3<T>&
  Matrix3<T>::operator*=(const T& scale) noexcept
  {
    *this = *this * scale;
    return *this;
  }
}