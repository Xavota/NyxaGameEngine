#include "pch.h"

#include "math/nyVector2.hpp"

using namespace nyEngineSDK;

namespace
{
  constexpr f32 kTolerance = 0.0001f;

  // ---------------------------------------------------------------------------
  // Constructors
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, DefaultConstructorInitializesToZero)
  {
    Vector2f vector;

    EXPECT_FLOAT_EQ(vector.x, 0.0f);
    EXPECT_FLOAT_EQ(vector.y, 0.0f);
  }

  TEST(Vector2Test, ComponentConstructorInitializesComponents)
  {
    Vector2f vector(3.0f, 4.0f);

    EXPECT_FLOAT_EQ(vector.x, 3.0f);
    EXPECT_FLOAT_EQ(vector.y, 4.0f);
  }

  TEST(Vector2Test, DirectionScaleConstructorScalesDirection)
  {
    Vector2f direction(2.0f, 3.0f);
    Vector2f vector(direction, 4.0f);

    EXPECT_FLOAT_EQ(vector.x, 8.0f);
    EXPECT_FLOAT_EQ(vector.y, 12.0f);
  }

  // ---------------------------------------------------------------------------
  // Constants
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, ZeroConstantIsCorrect)
  {
    EXPECT_FLOAT_EQ(Vector2f::kZERO.x, 0.0f);
    EXPECT_FLOAT_EQ(Vector2f::kZERO.y, 0.0f);
  }

  TEST(Vector2Test, RightConstantIsCorrect)
  {
    EXPECT_FLOAT_EQ(Vector2f::kRIGHT.x, 1.0f);
    EXPECT_FLOAT_EQ(Vector2f::kRIGHT.y, 0.0f);
  }

  TEST(Vector2Test, UpConstantIsCorrect)
  {
    EXPECT_FLOAT_EQ(Vector2f::kUP.x, 0.0f);
    EXPECT_FLOAT_EQ(Vector2f::kUP.y, 1.0f);
  }

  // ---------------------------------------------------------------------------
  // Indexing
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, IndexOperatorReturnsCorrectComponents)
  {
    Vector2f vector(3.0f, 7.0f);

    EXPECT_FLOAT_EQ(vector[0], 3.0f);
    EXPECT_FLOAT_EQ(vector[1], 7.0f);
  }

  TEST(Vector2Test, IndexOperatorCanModifyComponents)
  {
    Vector2f vector;

    vector[0] = 5.0f;
    vector[1] = 8.0f;

    EXPECT_FLOAT_EQ(vector.x, 5.0f);
    EXPECT_FLOAT_EQ(vector.y, 8.0f);
  }

  TEST(Vector2Test, ConstIndexOperatorReturnsCorrectComponents)
  {
    const Vector2f vector(3.0f, 7.0f);

    EXPECT_FLOAT_EQ(vector[0], 3.0f);
    EXPECT_FLOAT_EQ(vector[1], 7.0f);
  }

  // ---------------------------------------------------------------------------
  // Dot Product
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, DotProductReturnsCorrectValue)
  {
    Vector2f a(2.0f, 3.0f);
    Vector2f b(4.0f, 5.0f);

    EXPECT_FLOAT_EQ(a.dot(b), 23.0f);
  }

  TEST(Vector2Test, DotProductOfPerpendicularVectorsIsZero)
  {
    EXPECT_FLOAT_EQ(Vector2f::kRIGHT.dot(Vector2f::kUP), 0.0f);
  }

  TEST(Vector2Test, DotProductCanUseDifferentReturnType)
  {
    Vector2i a(2, 3);
    Vector2i b(4, 5);

    const f32 result = a.dot<f32>(b);

    EXPECT_FLOAT_EQ(result, 23.0f);
  }

  // ---------------------------------------------------------------------------
  // Cross Product
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, CrossProductReturnsCorrectValue)
  {
    Vector2f a(2.0f, 3.0f);
    Vector2f b(4.0f, 5.0f);

    EXPECT_FLOAT_EQ(a.cross(b), -2.0f);
  }

  TEST(Vector2Test, CrossProductIsPositiveForCounterClockwiseVector)
  {
    EXPECT_FLOAT_EQ(Vector2f::kRIGHT.cross(Vector2f::kUP), 1.0f);
  }

  TEST(Vector2Test, CrossProductIsNegativeForClockwiseVector)
  {
    EXPECT_FLOAT_EQ(Vector2f::kUP.cross(Vector2f::kRIGHT), -1.0f);
  }

  TEST(Vector2Test, CrossProductOfParallelVectorsIsZero)
  {
    Vector2f a(1.0f, 2.0f);
    Vector2f b(2.0f, 4.0f);

    EXPECT_FLOAT_EQ(a.cross(b), 0.0f);
  }

  // ---------------------------------------------------------------------------
  // Perpendicular
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, PerpendicularRotatesCounterClockwise90Degrees)
  {
    Vector2f vector(2.0f, 3.0f);

    Vector2f result = vector.perpendicular();

    EXPECT_FLOAT_EQ(result.x, -3.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
  }

  TEST(Vector2Test, PerpendicularVectorHasZeroDotProduct)
  {
    Vector2f vector(2.0f, 3.0f);

    Vector2f perpendicular = vector.perpendicular();

    EXPECT_FLOAT_EQ(vector.dot(perpendicular), 0.0f);
  }

  // ---------------------------------------------------------------------------
  // Distance
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, SquaredDistanceReturnsCorrectValue)
  {
    Vector2f a(1.0f, 2.0f);
    Vector2f b(4.0f, 6.0f);

    EXPECT_FLOAT_EQ(a.getSqrDistance(b), 25.0f);
  }

  TEST(Vector2Test, DistanceReturnsCorrectValue)
  {
    Vector2f a(1.0f, 2.0f);
    Vector2f b(4.0f, 6.0f);

    EXPECT_NEAR(a.getDistance(b), 5.0f, kTolerance);
  }

  TEST(Vector2Test, DistanceIsSymmetric)
  {
    Vector2f a(-3.0f, 5.0f);
    Vector2f b(8.0f, -2.0f);

    EXPECT_NEAR(a.getDistance(b),
                b.getDistance(a),
                kTolerance);
  }

  TEST(Vector2Test, DistanceFromVectorToItselfIsZero)
  {
    Vector2f vector(3.0f, 7.0f);

    EXPECT_FLOAT_EQ(vector.getDistance(vector), 0.0f);
  }

  TEST(Vector2Test, IntegerDistanceDefaultsToFloat)
  {
    Vector2i a(0, 0);
    Vector2i b(3, 4);

    const f32 distance = a.getDistance(b);

    EXPECT_FLOAT_EQ(distance, 5.0f);
  }

  // ---------------------------------------------------------------------------
  // Magnitude
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, SquaredMagnitudeReturnsCorrectValue)
  {
    Vector2f vector(3.0f, 4.0f);

    EXPECT_FLOAT_EQ(vector.getSqrMagnitude(), 25.0f);
  }

  TEST(Vector2Test, MagnitudeReturnsCorrectValue)
  {
    Vector2f vector(3.0f, 4.0f);

    EXPECT_NEAR(vector.getMagnitude(), 5.0f, kTolerance);
  }

  TEST(Vector2Test, ZeroVectorHasZeroMagnitude)
  {
    EXPECT_FLOAT_EQ(Vector2f::kZERO.getMagnitude(), 0.0f);
  }

  TEST(Vector2Test, IntegerMagnitudeDefaultsToFloat)
  {
    Vector2i vector(3, 4);

    const f32 magnitude = vector.getMagnitude();

    EXPECT_FLOAT_EQ(magnitude, 5.0f);
  }

  // ---------------------------------------------------------------------------
  // Normalization
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, GetNormalizedReturnsUnitVector)
  {
    Vector2f vector(3.0f, 4.0f);

    Vector2f result = vector.getNormalized();

    EXPECT_NEAR(result.x, 0.6f, kTolerance);
    EXPECT_NEAR(result.y, 0.8f, kTolerance);
    EXPECT_NEAR(result.getMagnitude(), 1.0f, kTolerance);
  }

  TEST(Vector2Test, GetNormalizedDoesNotModifyOriginal)
  {
    Vector2f vector(3.0f, 4.0f);

    vector.getNormalized();

    EXPECT_FLOAT_EQ(vector.x, 3.0f);
    EXPECT_FLOAT_EQ(vector.y, 4.0f);
  }

  TEST(Vector2Test, NormalizeModifiesOriginal)
  {
    Vector2f vector(3.0f, 4.0f);

    vector.normalize();

    EXPECT_NEAR(vector.x, 0.6f, kTolerance);
    EXPECT_NEAR(vector.y, 0.8f, kTolerance);
    EXPECT_NEAR(vector.getMagnitude(), 1.0f, kTolerance);
  }

  TEST(Vector2Test, NormalizingZeroVectorReturnsZeroVector)
  {
    Vector2f result = Vector2f::kZERO.getNormalized();

    EXPECT_EQ(result, Vector2f::kZERO);
  }

  // ---------------------------------------------------------------------------
  // Truncation / Resizing
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, GetTruncatedReturnsVectorWithRequestedMagnitude)
  {
    Vector2f vector(3.0f, 4.0f);

    Vector2f result = vector.getTruncated(10.0f);

    EXPECT_NEAR(result.x, 6.0f, kTolerance);
    EXPECT_NEAR(result.y, 8.0f, kTolerance);
    EXPECT_NEAR(result.getMagnitude(), 10.0f, kTolerance);
  }

  TEST(Vector2Test, GetTruncatedDoesNotModifyOriginal)
  {
    Vector2f vector(3.0f, 4.0f);

    vector.getTruncated(10.0f);

    EXPECT_FLOAT_EQ(vector.x, 3.0f);
    EXPECT_FLOAT_EQ(vector.y, 4.0f);
  }

  TEST(Vector2Test, TruncateModifiesOriginal)
  {
    Vector2f vector(3.0f, 4.0f);

    vector.truncate(10.0f);

    EXPECT_NEAR(vector.x, 6.0f, kTolerance);
    EXPECT_NEAR(vector.y, 8.0f, kTolerance);
  }

  TEST(Vector2Test, TruncatingZeroVectorReturnsZeroVector)
  {
    Vector2f result = Vector2f::kZERO.getTruncated(10.0f);

    EXPECT_EQ(result, Vector2f::kZERO);
  }

  // ---------------------------------------------------------------------------
  // Projection
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, ProjectionOntoXAxisReturnsXAxisComponent)
  {
    Vector2f a(3.0f, 4.0f);
    Vector2f b(1.0f, 0.0f);

    auto result = Vector2f::projection(a, b);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 3.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 0.0f, kTolerance);
  }

  TEST(Vector2Test, ProjectionOntoZeroVectorFails)
  {
    Vector2f a(3.0f, 4.0f);

    auto result = Vector2f::projection(a, Vector2f::kZERO);

    EXPECT_FALSE(result);
  }

  // ---------------------------------------------------------------------------
  // Rejection
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, RejectionReturnsPerpendicularComponent)
  {
    Vector2f a(3.0f, 4.0f);
    Vector2f b(1.0f, 0.0f);

    auto result = Vector2f::rejection(a, b);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 0.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 4.0f, kTolerance);
  }

  TEST(Vector2Test, RejectionOntoZeroVectorFails)
  {
    Vector2f a(3.0f, 4.0f);

    auto result = Vector2f::rejection(a, Vector2f::kZERO);

    EXPECT_FALSE(result);
  }

  // ---------------------------------------------------------------------------
  // Reflection
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, ReflectionAcrossUpNormalFlipsYComponent)
  {
    Vector2f vector(3.0f, -4.0f);

    auto result = Vector2f::reflection(vector, Vector2f::kUP);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 3.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 4.0f, kTolerance);
  }

  TEST(Vector2Test, ReflectionWithZeroNormalFails)
  {
    Vector2f vector(3.0f, -4.0f);

    auto result = Vector2f::reflection(vector, Vector2f::kZERO);

    EXPECT_FALSE(result);
  }

  // ---------------------------------------------------------------------------
  // Linear Interpolation
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, LerpAtZeroReturnsStart)
  {
    Vector2f a(0.0f, 10.0f);
    Vector2f b(10.0f, 20.0f);

    Vector2f result = Vector2f::lerp(a, b, 0.0f);

    EXPECT_NEAR(result.x, a.x, kTolerance);
    EXPECT_NEAR(result.y, a.y, kTolerance);
  }

  TEST(Vector2Test, LerpAtOneReturnsEnd)
  {
    Vector2f a(0.0f, 10.0f);
    Vector2f b(10.0f, 20.0f);

    Vector2f result = Vector2f::lerp(a, b, 1.0f);

    EXPECT_NEAR(result.x, b.x, kTolerance);
    EXPECT_NEAR(result.y, b.y, kTolerance);
  }

  TEST(Vector2Test, LerpAtHalfReturnsMidpoint)
  {
    Vector2f a(0.0f, 10.0f);
    Vector2f b(10.0f, 20.0f);

    Vector2f result = Vector2f::lerp(a, b, 0.5f);

    EXPECT_NEAR(result.x, 5.0f, kTolerance);
    EXPECT_NEAR(result.y, 15.0f, kTolerance);
  }

  TEST(Vector2Test, LerpSupportsCustomCurve)
  {
    Vector2f a(0.0f, 0.0f);
    Vector2f b(10.0f, 20.0f);

    auto squareCurve = [](f32 alpha) noexcept
    {
      return alpha * alpha;
    };

    Vector2f result =
      Vector2f::lerp(a, b, 0.5f, squareCurve);

    // 0.5^2 = 0.25
    EXPECT_NEAR(result.x, 2.5f, kTolerance);
    EXPECT_NEAR(result.y, 5.0f, kTolerance);
  }

  // ---------------------------------------------------------------------------
  // Vector Arithmetic
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, AdditionAddsComponents)
  {
    Vector2f a(2.0f, 3.0f);
    Vector2f b(4.0f, 5.0f);

    Vector2f result = a + b;

    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 8.0f);
  }

  TEST(Vector2Test, SubtractionSubtractsComponents)
  {
    Vector2f a(5.0f, 8.0f);
    Vector2f b(2.0f, 3.0f);

    Vector2f result = a - b;

    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 5.0f);
  }

  TEST(Vector2Test, ScalarAdditionAddsToBothComponents)
  {
    Vector2f vector(2.0f, 3.0f);

    Vector2f result = vector + 4.0f;

    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
  }

  TEST(Vector2Test, ScalarSubtractionSubtractsFromBothComponents)
  {
    Vector2f vector(5.0f, 8.0f);

    Vector2f result = vector - 2.0f;

    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
  }

  TEST(Vector2Test, ScalarMultiplicationMultipliesBothComponents)
  {
    Vector2f vector(2.0f, 3.0f);

    Vector2f result = vector * 4.0f;

    EXPECT_FLOAT_EQ(result.x, 8.0f);
    EXPECT_FLOAT_EQ(result.y, 12.0f);
  }

  TEST(Vector2Test, ScalarDivisionDividesBothComponents)
  {
    Vector2f vector(8.0f, 12.0f);

    Vector2f result = vector / 4.0f;

    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
  }

  TEST(Vector2Test, UnaryMinusNegatesComponents)
  {
    Vector2f vector(2.0f, -3.0f);

    Vector2f result = -vector;

    EXPECT_FLOAT_EQ(result.x, -2.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
  }

  // ---------------------------------------------------------------------------
  // Compound Assignment
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, AdditionAssignmentModifiesVector)
  {
    Vector2f vector(2.0f, 3.0f);

    vector += Vector2f(4.0f, 5.0f);

    EXPECT_EQ(vector, Vector2f(6.0f, 8.0f));
  }

  TEST(Vector2Test, SubtractionAssignmentModifiesVector)
  {
    Vector2f vector(5.0f, 8.0f);

    vector -= Vector2f(2.0f, 3.0f);

    EXPECT_EQ(vector, Vector2f(3.0f, 5.0f));
  }

  TEST(Vector2Test, ScalarAdditionAssignmentModifiesVector)
  {
    Vector2f vector(2.0f, 3.0f);

    vector += 4.0f;

    EXPECT_EQ(vector, Vector2f(6.0f, 7.0f));
  }

  TEST(Vector2Test, ScalarSubtractionAssignmentModifiesVector)
  {
    Vector2f vector(5.0f, 8.0f);

    vector -= 2.0f;

    EXPECT_EQ(vector, Vector2f(3.0f, 6.0f));
  }

  TEST(Vector2Test, ScalarMultiplicationAssignmentModifiesVector)
  {
    Vector2f vector(2.0f, 3.0f);

    vector *= 4.0f;

    EXPECT_EQ(vector, Vector2f(8.0f, 12.0f));
  }

  TEST(Vector2Test, ScalarDivisionAssignmentModifiesVector)
  {
    Vector2f vector(8.0f, 12.0f);

    vector /= 4.0f;

    EXPECT_EQ(vector, Vector2f(2.0f, 3.0f));
  }

  // ---------------------------------------------------------------------------
  // Equality
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, EqualityReturnsTrueForEqualVectors)
  {
    Vector2f a(2.0f, 3.0f);
    Vector2f b(2.0f, 3.0f);

    EXPECT_TRUE(a == b);
  }

  TEST(Vector2Test, EqualityReturnsFalseForDifferentVectors)
  {
    Vector2f a(2.0f, 3.0f);
    Vector2f b(2.0f, 4.0f);

    EXPECT_FALSE(a == b);
  }

  TEST(Vector2Test, InequalityReturnsTrueForDifferentVectors)
  {
    Vector2f a(2.0f, 3.0f);
    Vector2f b(2.0f, 4.0f);

    EXPECT_TRUE(a != b);
  }

  TEST(Vector2Test, InequalityReturnsFalseForEqualVectors)
  {
    Vector2f a(2.0f, 3.0f);
    Vector2f b(2.0f, 3.0f);

    EXPECT_FALSE(a != b);
  }

  // ---------------------------------------------------------------------------
  // Type Conversion
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, ExplicitConversionConvertsFloatToInteger)
  {
    Vector2f floatVector(3.7f, -2.4f);

    Vector2i intVector =
      static_cast<Vector2i>(floatVector);

    EXPECT_EQ(intVector.x, 3);
    EXPECT_EQ(intVector.y, -2);
  }

  TEST(Vector2Test, ExplicitConversionConvertsIntegerToFloat)
  {
    Vector2i intVector(3, -2);

    Vector2f floatVector =
      static_cast<Vector2f>(intVector);

    EXPECT_FLOAT_EQ(floatVector.x, 3.0f);
    EXPECT_FLOAT_EQ(floatVector.y, -2.0f);
  }

  // ---------------------------------------------------------------------------
  // String Conversion
  // ---------------------------------------------------------------------------

  TEST(Vector2Test, ToStringReturnsExpectedFormat)
  {
    Vector2i vector(3, -2);

    EXPECT_EQ(vector.toString(), "{ x:3, y:-2 }");
  }
}