/******************************************************************************/
/**
 * @file    nyMatrix4.hpp
 * @author  Dalia Castellanos
 * @date    14/09/2026
 * @brief   Defines the Matrix4 class for numerical operations.
 *
 * A simple 4 by 4 matrix class for numerical operations.
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
#include "math/nyMatrix3.h"
#include "math/nyVector3.hpp"

namespace nyEngineSDK
{
#if NY_CPP20
  template<Number T>
#else
  template<typename T>
#endif
  class NY_API Matrix4
  {
#if !NY_CPP20
    NY_STATIC_ASSERT(
      IsNumberV<T>,
      "Matrix4<T> requires a number type."
    );
#endif

   public:
    /**
     * @brief  Constructs a 4x4 matrix with the given array.
     */
    Matrix4(const Array<T, 16>& _m) : m(_m) {}
    /**
     * @brief  Constructs a 4x4 matrix with the given values.
     */
    Matrix4(const T& _m00, const T& _m01, const T& _m02, const T& _m03,
            const T& _m10, const T& _m11, const T& _m12, const T& _m13,
            const T& _m20, const T& _m21, const T& _m22, const T& _m23,
            const T& _m30, const T& _m31, const T& _m32, const T& _m33) :
    m({ _m00, _m01, _m02, _m03,
        _m10, _m11, _m12, _m13,
        _m20, _m21, _m22, _m23,
        _m30, _m31, _m32, _m33 }) {}

    /**
     * @brief  Creates a 3D rotation matrix from Euler angles with the last
     *         values on each column set to zero and the last row set to
     *         (0, 0, 0, 1).
               Used for 3D transformations with translations.
     * @param  angles  The Euler angles.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromAngle3D(const EulerAngles<T>& angles) noexcept;
    /**
     * @brief  Creates a 3D scale matrix from a scale 3D vector with the last
     *         values on each column set to zero and the last row set to
     *         (0, 0, 0, 1).
               Used for 3D transformations with translations.
     * @param  scale  The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromScale3D(const Vector3<T>& scale) noexcept;
    /**
     * @brief  Creates a 3D translation matrix from a translation 3D vector.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromTranslation3D(const Vector3<T>& translation) noexcept;
    /**
     * @brief  Creates a 3D transformation matrix from an angle and a
     *         3D scale vector.
               Used for 3D transformations with translations.
     * @param  angles  The Euler angles.
     * @param  scale   The scale vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromAngleScale3D(const EulerAngles<T>& angles, const Vector3<T>& scale) noexcept;
    /**
     * @brief  Creates a 3D transformation matrix from an angle and a
     *         translation 3D vector.
     * @param  angles       The Euler angles.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromAngleTranslation3D(const EulerAngles<T>& angles,
                           const Vector3<T>& translation) noexcept;
    /**
     * @brief  Creates a 3D transformation matrix from a scale 3D vector and
     *         a translation 3D vector.
     * @param  scale        The scale vector.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromScaleTranslation3D(const Vector3<T>& scale,
                           const Vector3<T>& translation) noexcept;
    /**
     * @brief  Creates a 3D transformation matrix from an angle,
     *         a scale 3D vector and a translation 3D vector.
     * @param  angles       The Euler angles.
     * @param  scale        The scale vector.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromAngleScaleTranslation3D(const EulerAngles<T>& angles,
                                const Vector3<T>& scale,
                                const Vector3<T>& translation) noexcept;

    /**
     * @brief  Creates a 3x3 matrix from three world axis vectors.
     * @param  axisX        The x-axis vector.
     * @param  axisY        The y-axis vector.
     * @param  axisZ        The z-axis vector.
     * @param  translation  The translation vector.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    fromWorldAxis(const Vector3<T>& axisX,
                  const Vector3<T>& axisY,
                  const Vector3<T>& axisZ,
                  const Vector3<T>& translation) noexcept;

    /**
     * @brief  Multiplies two matrices and returns the result.
     * @param  a  The first matrix.
     * @param  b  The second matrix.
     * @return The resulting matrix.
     */
    static NY_FORCE_INLINE NY_NODISCARD Matrix4
    multiply(const Matrix4& a, const Matrix4& b) noexcept;

    /**
     * @brief  Multiplies this matrix with another matrix. (this * other)
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
    multiply(const Matrix4& other) const noexcept;

    /**
     * @brief  Returns the transpose of this matrix.
     * @return The transposed matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
    getTransposed() const noexcept;
    /**
     * @brief  Transposes this matrix.
     * @return The transposed matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4&
    transpose() noexcept;

    /**
     * @brief  Returns the cofactor matrix of this matrix.
     * @return The cofactor matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
    getCofactor() const noexcept;

    /**
     * @brief  Returns the adjoint matrix of this matrix.
     * @return The adjoint matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
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
    NY_FORCE_INLINE NY_NODISCARD Result<Matrix4>
    getInversed() const noexcept;
    /**
     * @brief  Inverses this matrix.
     * @return The inverse matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Result<Matrix4&>
    invert() const noexcept;

    /**
     * @brief  Adds two matrices and returns the result.
     * @param  other  The matrix to add.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
    operator+(const Matrix4& other) const noexcept;
    /**
     * @brief  Subtracts two matrices and returns the result.
     * @param  other  The matrix to subtract.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
    operator-(const Matrix4& other) const noexcept;
    /**
     * @brief  Multiplies two matrices and returns the result.
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
    operator*(const Matrix4& other) const noexcept;
    /**
     * @brief  Multiplies every value of this matrix with a scalar and returns
     *         the result.
     * @param  other  The scalar to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4
    operator*(const T& scale) const noexcept;

    /**
     * @brief  Adds a matrix to this matrix.
     * @param  other  The matrix to add.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4&
    operator+=(const Matrix4& other) noexcept;
    /**
     * @brief  Subtracts a matrix from this matrix.
     * @param  other  The matrix to subtract.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4&
    operator-=(const Matrix4& other) noexcept;
    /**
     * @brief  Multiplies this matrix with another matrix.
     * @param  other  The matrix to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4&
    operator*=(const Matrix4& other) noexcept;
    /**
     * @brief  Multiplies every value of this matrix with a scalar.
     * @param  other  The scalar to multiply with.
     * @return The resulting matrix.
     */
    NY_FORCE_INLINE NY_NODISCARD Matrix4&
    operator*=(const T& scale) noexcept;

   private:
    union
    {
      struct
      {
        T m00, m01, m02, m03;
        T m10, m11, m12, m13;
        T m20, m21, m22, m23;
        T m30, m31, m32, m33;
      };
      Array<T, 16> m;
    };
  };

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromAngle3D(const EulerAngles<T>& angles) noexcept
  {
    Matrix4<T> rotationX(T(1),               T(0),                T(0), T(0),
                         T(0), angles.pitch.cos(), -angles.pitch.sin(), T(0),
                         T(0), angles.pitch.sin(),  angles.pitch.cos(), T(0),
                         T(0),               T(0),                T(0), T(1));
    Matrix4<T> rotationY( angles.pitch.cos(), T(0), angles.pitch.sin(), T(0),
                                        T(0), T(1),               T(0), T(0),
                         -angles.pitch.sin(), T(0), angles.pitch.cos(), T(0),
                                        T(0), T(0),               T(0), T(1));
    Matrix4<T> rotationZ(angles.pitch.cos(), -angles.pitch.sin(), T(0), T(0),
                         angles.pitch.sin(),  angles.pitch.cos(), T(0), T(0),
                                       T(0),                T(0), T(1), T(0));
    // TODO: EVENTUALLY THIS ORDER SHOULD BE CHANGED AT RUNTIME WITH USER PREFERENCES
    return rotationZ * rotationX * rotationY;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromScale3D(const Vector3<T>& scale) noexcept
  {
    return Matrix4(scale.x,    T(0),    T(0),    T(0),
                      T(0), scale.y,    T(0),    T(0),
                      T(0),    T(0), scale.z,    T(0),
                      T(0),    T(0),    T(0),    T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromTranslation3D(const Vector3<T>& translation) noexcept
  {
    return Matrix4(T(1), T(0), T(0), translation.x,
                   T(0), T(1), T(0), translation.y,
                   T(0), T(0), T(1), translation.z,
                   T(0), T(0), T(0),          T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromAngleScale3D(const EulerAngles<T>& angles,
                               const Vector3<T>& scale) noexcept
  {
    Matrix4<T> rotationMat = Matrix4<T>::fromAngle3D(angles);
    Matrix4<T> scaleMat = Matrix4<T>::fromScale3D(scale);
    return rotationMat * scaleMat;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromAngleTranslation3D(const EulerAngles<T>& angles,
                                     const Vector3<T>& translation) noexcept
  {
    Matrix4<T> translationMat = Matrix4<T>::fromTranslation3D(translation);
    Matrix4<T> rotationMat = Matrix4<T>::fromAngle3D(angles);
    return translationMat * rotationMat;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromScaleTranslation3D(const Vector3<T>& scale,
                                     const Vector3<T>& translation) noexcept
  {
    return Matrix4(scale.x,    T(0),    T(0), translation.x,
                      T(0), scale.y,    T(0), translation.y,
                      T(0),    T(0), scale.z, translation.z,
                      T(0),    T(0),    T(0),          T(1));
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromAngleScaleTranslation3D(const EulerAngles<T>& angles,
                                          const Vector3<T>& scale,
                                          const Vector3<T>& translation) noexcept
  {
    Matrix4<T> translationMat = Matrix4<T>::fromTranslation3D(translation);
    Matrix4<T> rotationMat = Matrix4<T>::fromAngle3D(angles);
    Matrix4<T> scaleMat = Matrix4<T>::fromScale3D(scale);
    return translationMat * rotationMat * scaleMat;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::fromWorldAxis(const Vector3<T>& axisX,
                            const Vector3<T>& axisY,
                            const Vector3<T>& axisZ,
                            const Vector3<T>& translation) noexcept
  {
    return Matrix4(axisX.x, axisY.x, axisZ.x, translation.x,
                   axisX.y, axisY.y, axisZ.y, translation.y,
                   axisX.z, axisY.z, axisZ.z, translation.z,
                   T(0),    T(0),    T(0),          T(1));
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::multiply(const Matrix4<T>& a, const Matrix4<T>& b) noexcept
  {
    return Matrix4(a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30,
                   a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31,
                   a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32,
                   a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,

                   a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30,
                   a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
                   a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
                   a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,

                   a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30,
                   a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
                   a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
                   a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,

                   a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30,
                   a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
                   a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
                   a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::multiply(const Matrix4<T>& other) const noexcept
  {
    return multiply(*this, other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::getTransposed() const noexcept
  {
    return Matrix4(m00, m10, m20, m30,
                   m01, m11, m21, m31,
                   m02, m12, m22, m32,
                   m03, m13, m23, m33);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>&
  Matrix4<T>::transpose() noexcept
  {
    *this = getTransposed();
    return *this;
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::getCofactor() const noexcept
  {
    T c00 = Matrix3<T>(m11, m12, m13,
                       m21, m22, m23,
                       m31, m32, m33).determinant();
    T c01 = Matrix3<T>(m10, m12, m13,
                       m20, m22, m23,
                       m30, m32, m33).determinant();
    T c02 = Matrix3<T>(m10, m11, m13,
                       m20, m21, m23,
                       m30, m31, m33).determinant();
    T c03 = Matrix3<T>(m10, m11, m12,
                       m20, m21, m22,
                       m30, m31, m32).determinant();

    T c10 = Matrix3<T>(m01, m02, m03,
                       m21, m22, m23,
                       m31, m32, m33).determinant();
    T c11 = Matrix3<T>(m00, m02, m03,
                       m20, m22, m23,
                       m30, m32, m33).determinant();
    T c12 = Matrix3<T>(m00, m01, m03,
                       m20, m21, m23,
                       m30, m31, m33).determinant();
    T c13 = Matrix3<T>(m00, m01, m02,
                       m20, m21, m22,
                       m30, m31, m32).determinant();

    T c20 = Matrix3<T>(m01, m02, m03,
                       m11, m12, m13,
                       m31, m32, m33).determinant();
    T c21 = Matrix3<T>(m00, m02, m03,
                       m10, m12, m13,
                       m30, m32, m33).determinant();
    T c22 = Matrix3<T>(m00, m01, m03,
                       m10, m11, m13,
                       m30, m31, m33).determinant();
    T c23 = Matrix3<T>(m00, m01, m02,
                       m10, m11, m12,
                       m30, m31, m32).determinant();

    T c30 = Matrix3<T>(m01, m02, m03,
                       m11, m12, m13,
                       m21, m22, m23).determinant();
    T c31 = Matrix3<T>(m00, m02, m03,
                       m10, m12, m13,
                       m20, m22, m23).determinant();
    T c32 = Matrix3<T>(m00, m01, m03,
                       m10, m11, m13,
                       m20, m21, m23).determinant();
    T c33 = Matrix3<T>(m00, m01, m02,
                       m10, m11, m12,
                       m20, m21, m22).determinant();

    return Matrix4( c00, -c01,  c02, -c03,
                   -c10,  c11, -c12,  c13,
                    c20, -c21,  c22, -c23,
                   -c30,  c31, -c32,  c33);
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::getAdjoint() const noexcept
  {
    return getCofactor().getTransposed();
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD T
  Matrix4<T>::determinant() const noexcept
  {
    Matrix3<T> subMatrix00(m11, m12, m13,
                           m21, m22, m23,
                           m31, m32, m33);
    Matrix3<T> subMatrix01(m10, m12, m13,
                           m20, m22, m23,
                           m30, m32, m33);
    Matrix3<T> subMatrix02(m10, m11, m13,
                           m20, m21, m23,
                           m30, m31, m33);
    Matrix3<T> subMatrix03(m10, m11, m12,
                           m20, m21, m22,
                           m30, m31, m32);
    return m00 * subMatrix00.determinant() -
           m01 * subMatrix01.determinant() +
           m02 * subMatrix02.determinant() -
           m03 * subMatrix03.determinant();
  }

  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Result<Matrix4<T>>
  Matrix4<T>::getInversed() const noexcept
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
  NY_FORCE_INLINE NY_NODISCARD Result<Matrix4<T>&>
  Matrix4<T>::invert() const noexcept
  {
    *this = getInversed();
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::operator+(const Matrix4<T>& other) const noexcept
  {
    return Matrix4(m00 + other.m00, m01 + other.m01, m02 + other.m02, m03 + other.m03,
                   m10 + other.m10, m11 + other.m11, m12 + other.m12, m13 + other.m13,
                   m20 + other.m20, m21 + other.m21, m22 + other.m22, m23 + other.m23,
                   m30 + other.m30, m31 + other.m31, m32 + other.m32, m33 + other.m33);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::operator-(const Matrix4<T>& other) const noexcept
  {
    return Matrix4(m00 - other.m00, m01 - other.m01, m02 - other.m02, m03 - other.m03,
                   m10 - other.m10, m11 - other.m11, m12 - other.m12, m13 - other.m13,
                   m20 - other.m20, m21 - other.m21, m22 - other.m22, m23 - other.m23,
                   m30 - other.m30, m31 - other.m31, m32 - other.m32, m33 - other.m33);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::operator*(const Matrix4<T>& other) const noexcept
  {
    return multiply(*this, other);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>
  Matrix4<T>::operator*(const T& scale) const noexcept
  {
    return Matrix4(m00 * scale, m01 * scale, m02 * scale, m03 * scale,
                   m10 * scale, m11 * scale, m12 * scale, m13 * scale,
                   m20 * scale, m21 * scale, m22 * scale, m23 * scale,
                   m30 * scale, m31 * scale, m32 * scale, m33 * scale);
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>&
  Matrix4<T>::operator+=(const Matrix4<T>& other) noexcept
  {
    *this = *this + other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>&
  Matrix4<T>::operator-=(const Matrix4<T>& other) noexcept
  {
    *this = *this - other;
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>&
  Matrix4<T>::operator*=(const Matrix4<T>& other) noexcept
  {
    *this = multiply(*this, other);
    return *this;
  }
  template<typename T>
  NY_FORCE_INLINE NY_NODISCARD Matrix4<T>&
  Matrix4<T>::operator*=(const T& scale) noexcept
  {
    *this = *this * scale;
    return *this;
  }
}