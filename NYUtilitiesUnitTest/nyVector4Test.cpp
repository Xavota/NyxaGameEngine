#include "pch.h"

#include "nyWhatToTest.h"

#if NY_TEST_VECTOR4 == 1

#include "nyAssertTestUtility.h"

#include <math/nyVector4.hpp>

using namespace nyEngineSDK;

namespace
{
  constexpr f32 kTolerance = 1e-5f;
}

// ============================================================================
// Constructors
// ============================================================================

TEST(Vector4Test, DefaultConstructorInitializesToZero)
{
  const Vector4f vector;

  EXPECT_FLOAT_EQ(vector.x, 0.0f);
  EXPECT_FLOAT_EQ(vector.y, 0.0f);
  EXPECT_FLOAT_EQ(vector.z, 0.0f);
  EXPECT_FLOAT_EQ(vector.w, 0.0f);
}

TEST(Vector4Test, ComponentConstructorInitializesComponents)
{
  const Vector4i vector(1, 2, 3, 4);

  EXPECT_EQ(vector.x, 1);
  EXPECT_EQ(vector.y, 2);
  EXPECT_EQ(vector.z, 3);
  EXPECT_EQ(vector.w, 4);
}

TEST(Vector4Test, DirectionScaleConstructorScalesVector)
{
  const Vector4i direction(1, 2, 3, 4);
  const Vector4i vector(direction, 3);

  EXPECT_EQ(vector, Vector4i(3, 6, 9, 12));
}

// ============================================================================
// Constants
// ============================================================================

TEST(Vector4Test, ZeroConstantIsCorrect)
{
  EXPECT_EQ(Vector4i::kZERO, Vector4i(0, 0, 0, 0));
}

TEST(Vector4Test, RightConstantIsCorrect)
{
  EXPECT_EQ(Vector4i::kRIGHT, Vector4i(1, 0, 0, 0));
}

TEST(Vector4Test, UpConstantIsCorrect)
{
  EXPECT_EQ(Vector4i::kUP, Vector4i(0, 1, 0, 0));
}

TEST(Vector4Test, ForwardConstantIsCorrect)
{
  EXPECT_EQ(Vector4i::kFORWARD, Vector4i(0, 0, 1, 0));
}

TEST(Vector4Test, WConstantIsCorrect)
{
  EXPECT_EQ(Vector4i::kW, Vector4i(0, 0, 0, 1));
}

// ============================================================================
// Indexing
// ============================================================================

TEST(Vector4Test, IndexOperatorReturnsCorrectComponents)
{
  const Vector4i vector(10, 20, 30, 40);

  EXPECT_EQ(vector[0], 10);
  EXPECT_EQ(vector[1], 20);
  EXPECT_EQ(vector[2], 30);
  EXPECT_EQ(vector[3], 40);
}

TEST(Vector4Test, IndexOperatorCanModifyComponents)
{
  Vector4i vector(10, 20, 30, 40);

  vector[0] = 100;
  vector[1] = 200;
  vector[2] = 300;
  vector[3] = 400;

  EXPECT_EQ(vector, Vector4i(100, 200, 300, 400));
}

TEST(Vector4Test, ConstIndexOperatorReturnsConstComponents)
{
  const Vector4i vector(10, 20, 30, 40);

  const i32& x = vector[0];
  const i32& y = vector[1];
  const i32& z = vector[2];
  const i32& w = vector[3];

  EXPECT_EQ(x, 10);
  EXPECT_EQ(y, 20);
  EXPECT_EQ(z, 30);
  EXPECT_EQ(w, 40);
}

TEST(Vector4Test, IndexOperatorAssertsWhenIndexIsOutOfBounds)
{
#if NY_ENABLE_ASSERTS
  assertTestUtility::resetAssertCapture();

  assertTestUtility::AssertHandlerGuard guard(
    &assertTestUtility::testAssertHandler
  );

  Vector4i vector(10, 20, 30, 40);

  NY_MAYBE_UNUSED i32 value = vector[4];

  EXPECT_TRUE(assertTestUtility::gAssertCapture.triggered);
  EXPECT_STREQ(
    assertTestUtility::gAssertCapture.expression,
    "index < 4"
  );
#endif
}

TEST(Vector4Test, ConstIndexOperatorAssertsWhenIndexIsOutOfBounds)
{
#if NY_ENABLE_ASSERTS
  assertTestUtility::resetAssertCapture();

  assertTestUtility::AssertHandlerGuard guard(
    &assertTestUtility::testAssertHandler
  );

  const Vector4i vector(10, 20, 30, 40);

  NY_MAYBE_UNUSED i32 value = vector[4];

  EXPECT_TRUE(assertTestUtility::gAssertCapture.triggered);
  EXPECT_STREQ(
    assertTestUtility::gAssertCapture.expression,
    "index < 4"
  );
#endif
}

// ============================================================================
// Dot Product
// ============================================================================

TEST(Vector4Test, DotProductReturnsExpectedValue)
{
  const Vector4i a(1, 2, 3, 4);
  const Vector4i b(5, 6, 7, 8);

  // 5 + 12 + 21 + 32 = 70
  EXPECT_EQ(a.dot(b), 70);
}

TEST(Vector4Test, OrthogonalBasisVectorsHaveZeroDotProduct)
{
  EXPECT_EQ(Vector4i::kRIGHT.dot(Vector4i::kUP), 0);
  EXPECT_EQ(Vector4i::kRIGHT.dot(Vector4i::kFORWARD), 0);
  EXPECT_EQ(Vector4i::kRIGHT.dot(Vector4i::kW), 0);

  EXPECT_EQ(Vector4i::kUP.dot(Vector4i::kFORWARD), 0);
  EXPECT_EQ(Vector4i::kUP.dot(Vector4i::kW), 0);

  EXPECT_EQ(Vector4i::kFORWARD.dot(Vector4i::kW), 0);
}

TEST(Vector4Test, DotProductWithSelfEqualsSquaredMagnitude)
{
  const Vector4i vector(1, 2, 3, 4);

  EXPECT_EQ(vector.dot(vector), vector.getSqrMagnitude());
}

// ============================================================================
// Squared Distance
// ============================================================================

TEST(Vector4Test, SquaredDistanceReturnsExpectedValue)
{
  const Vector4i a(1, 2, 3, 4);
  const Vector4i b(2, 4, 5, 8);

  // 1^2 + 2^2 + 2^2 + 4^2 = 25
  EXPECT_EQ(a.getSqrDistance(b), 25);
}

TEST(Vector4Test, SquaredDistanceIsSymmetric)
{
  const Vector4i a(1, 2, 3, 4);
  const Vector4i b(2, 4, 5, 8);

  EXPECT_EQ(a.getSqrDistance(b), b.getSqrDistance(a));
}

TEST(Vector4Test, SquaredDistanceToSelfIsZero)
{
  const Vector4i vector(1, 2, 3, 4);

  EXPECT_EQ(vector.getSqrDistance(vector), 0);
}

// ============================================================================
// Distance
// ============================================================================

TEST(Vector4Test, DistanceReturnsExpectedValue)
{
  const Vector4f a(1.0f, 2.0f, 3.0f, 4.0f);
  const Vector4f b(2.0f, 4.0f, 5.0f, 8.0f);

  EXPECT_FLOAT_EQ(a.getDistance(b), 5.0f);
}

TEST(Vector4Test, DistanceIsSymmetric)
{
  const Vector4f a(1.0f, 2.0f, 3.0f, 4.0f);
  const Vector4f b(2.0f, 4.0f, 5.0f, 8.0f);

  EXPECT_FLOAT_EQ(
    a.getDistance(b),
    b.getDistance(a)
  );
}

TEST(Vector4Test, DistanceToSelfIsZero)
{
  const Vector4f vector(1.0f, 2.0f, 3.0f, 4.0f);

  EXPECT_FLOAT_EQ(vector.getDistance(vector), 0.0f);
}

TEST(Vector4Test, IntegerDistanceDefaultsToFloat)
{
  const Vector4i a(0, 0, 0, 0);
  const Vector4i b(1, 2, 2, 4);

  const f32 result = a.getDistance(b);

  EXPECT_FLOAT_EQ(result, 5.0f);
}

TEST(Vector4Test, IntegerDistanceCanReturnDouble)
{
  const Vector4i a(0, 0, 0, 0);
  const Vector4i b(1, 2, 2, 4);

  const f64 result = a.getDistance<f64>(b);

  EXPECT_DOUBLE_EQ(result, 5.0);
}

// ============================================================================
// Magnitude
// ============================================================================

TEST(Vector4Test, SquaredMagnitudeReturnsExpectedValue)
{
  const Vector4i vector(1, 2, 2, 4);

  EXPECT_EQ(vector.getSqrMagnitude(), 25);
}

TEST(Vector4Test, MagnitudeReturnsExpectedValue)
{
  const Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  EXPECT_FLOAT_EQ(vector.getMagnitude(), 5.0f);
}

TEST(Vector4Test, ZeroVectorHasZeroMagnitude)
{
  EXPECT_FLOAT_EQ(
    Vector4f::kZERO.getMagnitude(),
    0.0f
  );
}

TEST(Vector4Test, IntegerMagnitudeDefaultsToFloat)
{
  const Vector4i vector(1, 2, 2, 4);

  const f32 result = vector.getMagnitude();

  EXPECT_FLOAT_EQ(result, 5.0f);
}

TEST(Vector4Test, IntegerMagnitudeCanReturnDouble)
{
  const Vector4i vector(1, 2, 2, 4);

  const f64 result = vector.getMagnitude<f64>();

  EXPECT_DOUBLE_EQ(result, 5.0);
}

// ============================================================================
// Normalization
// ============================================================================

TEST(Vector4Test, GetNormalizedReturnsUnitVector)
{
  const Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  const Vector4f result = vector.getNormalized();

  EXPECT_NEAR(result.getMagnitude(), 1.0f, kTolerance);

  EXPECT_NEAR(result.x, 1.0f / 5.0f, kTolerance);
  EXPECT_NEAR(result.y, 2.0f / 5.0f, kTolerance);
  EXPECT_NEAR(result.z, 2.0f / 5.0f, kTolerance);
  EXPECT_NEAR(result.w, 4.0f / 5.0f, kTolerance);
}

TEST(Vector4Test, GetNormalizedDoesNotModifyOriginal)
{
  const Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  NY_MAYBE_UNUSED const Vector4f result =
    vector.getNormalized();

  EXPECT_EQ(
    vector,
    Vector4f(1.0f, 2.0f, 2.0f, 4.0f)
  );
}

TEST(Vector4Test, NormalizeModifiesOriginal)
{
  Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  vector.normalize();

  EXPECT_NEAR(vector.getMagnitude(), 1.0f, kTolerance);

  EXPECT_NEAR(vector.x, 1.0f / 5.0f, kTolerance);
  EXPECT_NEAR(vector.y, 2.0f / 5.0f, kTolerance);
  EXPECT_NEAR(vector.z, 2.0f / 5.0f, kTolerance);
  EXPECT_NEAR(vector.w, 4.0f / 5.0f, kTolerance);
}

TEST(Vector4Test, NormalizeReturnsNormalizedVector)
{
  Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  const Vector4f result = vector.normalize();

  EXPECT_EQ(result, vector);
}

TEST(Vector4Test, GetNormalizedZeroVectorReturnsZero)
{
  const Vector4f result =
    Vector4f::kZERO.getNormalized();

  EXPECT_EQ(result, Vector4f::kZERO);
}

TEST(Vector4Test, IntegerGetNormalizedDefaultsToFloatVector)
{
  const Vector4i vector(1, 2, 2, 4);

  const Vector4f result = vector.getNormalized();

  EXPECT_NEAR(result.x, 1.0f / 5.0f, kTolerance);
  EXPECT_NEAR(result.y, 2.0f / 5.0f, kTolerance);
  EXPECT_NEAR(result.z, 2.0f / 5.0f, kTolerance);
  EXPECT_NEAR(result.w, 4.0f / 5.0f, kTolerance);
}

TEST(Vector4Test, IntegerGetNormalizedCanReturnDoubleVector)
{
  const Vector4i vector(1, 2, 2, 4);

  const Vector4<f64> result =
    vector.getNormalized<f64>();

  EXPECT_NEAR(result.x, 1.0 / 5.0, 1e-12);
  EXPECT_NEAR(result.y, 2.0 / 5.0, 1e-12);
  EXPECT_NEAR(result.z, 2.0 / 5.0, 1e-12);
  EXPECT_NEAR(result.w, 4.0 / 5.0, 1e-12);
}

// ============================================================================
// Truncation
// ============================================================================

TEST(Vector4Test, GetTruncatedReturnsRequestedMagnitude)
{
  const Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  const Vector4f result =
    vector.getTruncated(10.0f);

  EXPECT_NEAR(result.getMagnitude(), 10.0f, kTolerance);

  EXPECT_NEAR(result.x, 2.0f, kTolerance);
  EXPECT_NEAR(result.y, 4.0f, kTolerance);
  EXPECT_NEAR(result.z, 4.0f, kTolerance);
  EXPECT_NEAR(result.w, 8.0f, kTolerance);
}

TEST(Vector4Test, GetTruncatedDoesNotModifyOriginal)
{
  const Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  NY_MAYBE_UNUSED const Vector4f result =
    vector.getTruncated(10.0f);

  EXPECT_EQ(
    vector,
    Vector4f(1.0f, 2.0f, 2.0f, 4.0f)
  );
}

TEST(Vector4Test, TruncateModifiesOriginal)
{
  Vector4f vector(1.0f, 2.0f, 2.0f, 4.0f);

  vector.truncate(10.0f);

  EXPECT_NEAR(vector.getMagnitude(), 10.0f, kTolerance);

  EXPECT_NEAR(vector.x, 2.0f, kTolerance);
  EXPECT_NEAR(vector.y, 4.0f, kTolerance);
  EXPECT_NEAR(vector.z, 4.0f, kTolerance);
  EXPECT_NEAR(vector.w, 8.0f, kTolerance);
}

TEST(Vector4Test, GetTruncatedZeroVectorReturnsZero)
{
  const Vector4f result =
    Vector4f::kZERO.getTruncated(10.0f);

  EXPECT_EQ(result, Vector4f::kZERO);
}

TEST(Vector4Test, IntegerGetTruncatedDefaultsToFloatVector)
{
  const Vector4i vector(1, 2, 2, 4);

  const Vector4f result =
    vector.getTruncated(10.0f);

  EXPECT_NEAR(result.x, 2.0f, kTolerance);
  EXPECT_NEAR(result.y, 4.0f, kTolerance);
  EXPECT_NEAR(result.z, 4.0f, kTolerance);
  EXPECT_NEAR(result.w, 8.0f, kTolerance);
}

// ============================================================================
// Projection
// ============================================================================

TEST(Vector4Test, ProjectionOntoXAxisReturnsXComponent)
{
  const Vector4f vector(3.0f, 4.0f, 5.0f, 6.0f);

  auto result =
    Vector4f::projection(vector, Vector4f::kRIGHT);

  ASSERT_TRUE(result);

  EXPECT_EQ(
    result.value(),
    Vector4f(3.0f, 0.0f, 0.0f, 0.0f)
  );
}

TEST(Vector4Test, ProjectionOntoWAxisReturnsWComponent)
{
  const Vector4f vector(3.0f, 4.0f, 5.0f, 6.0f);

  auto result =
    Vector4f::projection(vector, Vector4f::kW);

  ASSERT_TRUE(result);

  EXPECT_EQ(
    result.value(),
    Vector4f(0.0f, 0.0f, 0.0f, 6.0f)
  );
}

TEST(Vector4Test, ProjectionOntoNonUnitVectorWorks)
{
  const Vector4f a(3.0f, 4.0f, 5.0f, 6.0f);
  const Vector4f b(2.0f, 0.0f, 0.0f, 0.0f);

  auto result = Vector4f::projection(a, b);

  ASSERT_TRUE(result);

  EXPECT_NEAR(result.value().x, 3.0f, kTolerance);
  EXPECT_NEAR(result.value().y, 0.0f, kTolerance);
  EXPECT_NEAR(result.value().z, 0.0f, kTolerance);
  EXPECT_NEAR(result.value().w, 0.0f, kTolerance);
}

TEST(Vector4Test, ProjectionOntoZeroVectorFails)
{
  const Vector4f vector(3.0f, 4.0f, 5.0f, 6.0f);

  auto result =
    Vector4f::projection(vector, Vector4f::kZERO);

  EXPECT_FALSE(result);
}

TEST(Vector4Test, IntegerProjectionDefaultsToFloatVector)
{
  const Vector4i a(1, 1, 2, 3);
  const Vector4i b(2, 0, 0, 0);

  auto result = Vector4i::projection(a, b);

  ASSERT_TRUE(result);

  const Vector4f projected = result.value();

  EXPECT_NEAR(projected.x, 1.0f, kTolerance);
  EXPECT_NEAR(projected.y, 0.0f, kTolerance);
  EXPECT_NEAR(projected.z, 0.0f, kTolerance);
  EXPECT_NEAR(projected.w, 0.0f, kTolerance);
}

// ============================================================================
// Rejection
// ============================================================================

TEST(Vector4Test, RejectionRemovesProjectedComponent)
{
  const Vector4f vector(3.0f, 4.0f, 5.0f, 6.0f);

  auto result =
    Vector4f::rejection(vector, Vector4f::kRIGHT);

  ASSERT_TRUE(result);

  EXPECT_EQ(
    result.value(),
    Vector4f(0.0f, 4.0f, 5.0f, 6.0f)
  );
}

TEST(Vector4Test, ProjectionPlusRejectionReconstructsOriginal)
{
  const Vector4f a(3.0f, 4.0f, 5.0f, 6.0f);
  const Vector4f b(2.0f, 1.0f, 3.0f, 1.0f);

  auto projection = Vector4f::projection(a, b);
  auto rejection = Vector4f::rejection(a, b);

  ASSERT_TRUE(projection);
  ASSERT_TRUE(rejection);

  const Vector4f reconstructed =
    projection.value() + rejection.value();

  EXPECT_NEAR(reconstructed.x, a.x, kTolerance);
  EXPECT_NEAR(reconstructed.y, a.y, kTolerance);
  EXPECT_NEAR(reconstructed.z, a.z, kTolerance);
  EXPECT_NEAR(reconstructed.w, a.w, kTolerance);
}

TEST(Vector4Test, RejectionOntoZeroVectorFails)
{
  const Vector4f vector(3.0f, 4.0f, 5.0f, 6.0f);

  auto result =
    Vector4f::rejection(vector, Vector4f::kZERO);

  EXPECT_FALSE(result);
}

TEST(Vector4Test, IntegerRejectionDefaultsToFloatVector)
{
  const Vector4i a(1, 1, 2, 3);
  const Vector4i b(2, 0, 0, 0);

  auto result = Vector4i::rejection(a, b);

  ASSERT_TRUE(result);

  const Vector4f rejected = result.value();

  EXPECT_NEAR(rejected.x, 0.0f, kTolerance);
  EXPECT_NEAR(rejected.y, 1.0f, kTolerance);
  EXPECT_NEAR(rejected.z, 2.0f, kTolerance);
  EXPECT_NEAR(rejected.w, 3.0f, kTolerance);
}

// ============================================================================
// Reflection
// ============================================================================

TEST(Vector4Test, ReflectionAcrossUpNormalFlipsYComponent)
{
  const Vector4f vector(3.0f, -4.0f, 5.0f, 6.0f);

  auto result =
    Vector4f::reflection(vector, Vector4f::kUP);

  ASSERT_TRUE(result);

  EXPECT_EQ(
    result.value(),
    Vector4f(3.0f, 4.0f, 5.0f, 6.0f)
  );
}

TEST(Vector4Test, ReflectionPreservesMagnitude)
{
  const Vector4f vector(3.0f, -4.0f, 5.0f, 6.0f);
  const Vector4f normal(1.0f, 2.0f, 0.0f, 1.0f);

  auto result =
    Vector4f::reflection(vector, normal);

  ASSERT_TRUE(result);

  EXPECT_NEAR(
    result.value().getMagnitude(),
    vector.getMagnitude(),
    kTolerance
  );
}

TEST(Vector4Test, ReflectionWithZeroNormalFails)
{
  const Vector4f vector(3.0f, -4.0f, 5.0f, 6.0f);

  auto result =
    Vector4f::reflection(vector, Vector4f::kZERO);

  EXPECT_FALSE(result);
}

TEST(Vector4Test, IntegerReflectionDefaultsToFloatVector)
{
  const Vector4i vector(3, -4, 5, 6);
  const Vector4i normal(0, 2, 0, 0);

  auto result =
    Vector4i::reflection(vector, normal);

  ASSERT_TRUE(result);

  const Vector4f reflected = result.value();

  EXPECT_NEAR(reflected.x, 3.0f, kTolerance);
  EXPECT_NEAR(reflected.y, 4.0f, kTolerance);
  EXPECT_NEAR(reflected.z, 5.0f, kTolerance);
  EXPECT_NEAR(reflected.w, 6.0f, kTolerance);
}

// ============================================================================
// Lerp
// ============================================================================

TEST(Vector4Test, LerpAtZeroReturnsStart)
{
  const Vector4f a(1.0f, 2.0f, 3.0f, 4.0f);
  const Vector4f b(5.0f, 6.0f, 7.0f, 8.0f);

  EXPECT_EQ(
    Vector4f::lerp(a, b, 0.0f),
    a
  );
}

TEST(Vector4Test, LerpAtOneReturnsEnd)
{
  const Vector4f a(1.0f, 2.0f, 3.0f, 4.0f);
  const Vector4f b(5.0f, 6.0f, 7.0f, 8.0f);

  EXPECT_EQ(
    Vector4f::lerp(a, b, 1.0f),
    b
  );
}

TEST(Vector4Test, LerpAtHalfReturnsMidpoint)
{
  const Vector4f a(0.0f, 2.0f, 4.0f, 6.0f);
  const Vector4f b(10.0f, 6.0f, 8.0f, 10.0f);

  const Vector4f result =
    Vector4f::lerp(a, b, 0.5f);

  EXPECT_EQ(
    result,
    Vector4f(5.0f, 4.0f, 6.0f, 8.0f)
  );
}

TEST(Vector4Test, IntegerLerpDefaultsToFloatVector)
{
  const Vector4i a(0, 0, 0, 0);
  const Vector4i b(10, 20, 30, 40);

  const Vector4f result =
    Vector4i::lerp(a, b, 0.5f);

  EXPECT_EQ(
    result,
    Vector4f(5.0f, 10.0f, 15.0f, 20.0f)
  );
}

TEST(Vector4Test, LerpCanUseDoubleAlpha)
{
  const Vector4i a(0, 0, 0, 0);
  const Vector4i b(10, 20, 30, 40);

  const Vector4<f64> result =
    Vector4i::lerp<f64>(a, b, 0.25);

  EXPECT_DOUBLE_EQ(result.x, 2.5);
  EXPECT_DOUBLE_EQ(result.y, 5.0);
  EXPECT_DOUBLE_EQ(result.z, 7.5);
  EXPECT_DOUBLE_EQ(result.w, 10.0);
}

TEST(Vector4Test, LerpWithCurveTransformsAlpha)
{
  const Vector4f a(0.0f, 0.0f, 0.0f, 0.0f);
  const Vector4f b(10.0f, 20.0f, 30.0f, 40.0f);

  auto quadratic = [](f32 alpha) noexcept
  {
    return alpha * alpha;
  };

  const Vector4f result =
    Vector4f::lerp(a, b, 0.5f, quadratic);

  // Curve transforms 0.5 into 0.25.
  EXPECT_NEAR(result.x, 2.5f, kTolerance);
  EXPECT_NEAR(result.y, 5.0f, kTolerance);
  EXPECT_NEAR(result.z, 7.5f, kTolerance);
  EXPECT_NEAR(result.w, 10.0f, kTolerance);
}

// ============================================================================
// Homogenization
// ============================================================================

TEST(Vector4Test, GetHomogenizedDividesXYZByWAndSetsWToOne)
{
  const Vector4f vector(
    10.0f, 20.0f, 30.0f, 2.0f
  );

  auto result = vector.getHomogenized();

  ASSERT_TRUE(result);

  EXPECT_NEAR(result.value().x, 5.0f, kTolerance);
  EXPECT_NEAR(result.value().y, 10.0f, kTolerance);
  EXPECT_NEAR(result.value().z, 15.0f, kTolerance);
  EXPECT_FLOAT_EQ(result.value().w, 1.0f);
}

TEST(Vector4Test, GetHomogenizedDoesNotModifyOriginal)
{
  const Vector4f vector(
    10.0f, 20.0f, 30.0f, 2.0f
  );

  auto result = vector.getHomogenized();

  ASSERT_TRUE(result);

  EXPECT_EQ(
    vector,
    Vector4f(10.0f, 20.0f, 30.0f, 2.0f)
  );
}

TEST(Vector4Test, HomogenizeModifiesOriginal)
{
  Vector4f vector(
    10.0f, 20.0f, 30.0f, 2.0f
  );

  auto result = vector.homogenize();

  ASSERT_TRUE(result);

  EXPECT_NEAR(vector.x, 5.0f, kTolerance);
  EXPECT_NEAR(vector.y, 10.0f, kTolerance);
  EXPECT_NEAR(vector.z, 15.0f, kTolerance);
  EXPECT_FLOAT_EQ(vector.w, 1.0f);
}

TEST(Vector4Test, HomogenizeReturnsHomogenizedVector)
{
  Vector4f vector(
    10.0f, 20.0f, 30.0f, 2.0f
  );

  auto result = vector.homogenize();

  ASSERT_TRUE(result);

  EXPECT_EQ(result.value(), vector);
}

TEST(Vector4Test, GetHomogenizedWithWOneReturnsSameVector)
{
  const Vector4f vector(
    10.0f, 20.0f, 30.0f, 1.0f
  );

  auto result = vector.getHomogenized();

  ASSERT_TRUE(result);

  EXPECT_EQ(result.value(), vector);
}

TEST(Vector4Test, GetHomogenizedWithZeroWFails)
{
  const Vector4f vector(
    10.0f, 20.0f, 30.0f, 0.0f
  );

  auto result = vector.getHomogenized();

  EXPECT_FALSE(result);
}

TEST(Vector4Test, HomogenizeWithZeroWFailsAndDoesNotModifyVector)
{
  Vector4f vector(
    10.0f, 20.0f, 30.0f, 0.0f
  );

  const Vector4f original = vector;

  auto result = vector.homogenize();

  EXPECT_FALSE(result);
  EXPECT_EQ(vector, original);
}

// New behavior: integer vectors can produce floating-point homogeneous vectors.
TEST(Vector4Test, IntegerGetHomogenizedDefaultsToFloatVector)
{
  const Vector4i vector(1, 2, 3, 2);

  auto result = vector.getHomogenized();

  ASSERT_TRUE(result);

  const Vector4f homogenized = result.value();

  EXPECT_NEAR(homogenized.x, 0.5f, kTolerance);
  EXPECT_NEAR(homogenized.y, 1.0f, kTolerance);
  EXPECT_NEAR(homogenized.z, 1.5f, kTolerance);
  EXPECT_FLOAT_EQ(homogenized.w, 1.0f);
}

TEST(Vector4Test, IntegerGetHomogenizedCanReturnDoubleVector)
{
  const Vector4i vector(1, 2, 3, 2);

  auto result = vector.getHomogenized<f64>();

  ASSERT_TRUE(result);

  const Vector4<f64> homogenized = result.value();

  EXPECT_DOUBLE_EQ(homogenized.x, 0.5);
  EXPECT_DOUBLE_EQ(homogenized.y, 1.0);
  EXPECT_DOUBLE_EQ(homogenized.z, 1.5);
  EXPECT_DOUBLE_EQ(homogenized.w, 1.0);
}

// ============================================================================
// Vector Arithmetic
// ============================================================================

TEST(Vector4Test, VectorAdditionAddsComponents)
{
  const Vector4i a(1, 2, 3, 4);
  const Vector4i b(5, 6, 7, 8);

  EXPECT_EQ(a + b, Vector4i(6, 8, 10, 12));
}

TEST(Vector4Test, VectorSubtractionSubtractsComponents)
{
  const Vector4i a(6, 8, 10, 12);
  const Vector4i b(5, 6, 7, 8);

  EXPECT_EQ(a - b, Vector4i(1, 2, 3, 4));
}

// ============================================================================
// Scalar Arithmetic
// ============================================================================

TEST(Vector4Test, ScalarAdditionAddsToEveryComponent)
{
  EXPECT_EQ(
    Vector4i(1, 2, 3, 4) + 2,
    Vector4i(3, 4, 5, 6)
  );
}

TEST(Vector4Test, ScalarSubtractionSubtractsFromEveryComponent)
{
  EXPECT_EQ(
    Vector4i(3, 4, 5, 6) - 2,
    Vector4i(1, 2, 3, 4)
  );
}

TEST(Vector4Test, ScalarMultiplicationMultipliesEveryComponent)
{
  EXPECT_EQ(
    Vector4i(1, 2, 3, 4) * 3,
    Vector4i(3, 6, 9, 12)
  );
}

TEST(Vector4Test, ScalarDivisionDividesEveryComponent)
{
  EXPECT_EQ(
    Vector4i(6, 12, 18, 24) / 3,
    Vector4i(2, 4, 6, 8)
  );
}

// ============================================================================
// Unary Minus
// ============================================================================

TEST(Vector4Test, UnaryMinusNegatesEveryComponent)
{
  EXPECT_EQ(
    -Vector4i(1, -2, 3, -4),
    Vector4i(-1, 2, -3, 4)
  );
}

// ============================================================================
// Compound Assignment
// ============================================================================

TEST(Vector4Test, VectorAdditionAssignmentModifiesVector)
{
  Vector4i vector(1, 2, 3, 4);

  vector += Vector4i(5, 6, 7, 8);

  EXPECT_EQ(vector, Vector4i(6, 8, 10, 12));
}

TEST(Vector4Test, VectorSubtractionAssignmentModifiesVector)
{
  Vector4i vector(6, 8, 10, 12);

  vector -= Vector4i(5, 6, 7, 8);

  EXPECT_EQ(vector, Vector4i(1, 2, 3, 4));
}

TEST(Vector4Test, ScalarAdditionAssignmentModifiesVector)
{
  Vector4i vector(1, 2, 3, 4);

  vector += 2;

  EXPECT_EQ(vector, Vector4i(3, 4, 5, 6));
}

TEST(Vector4Test, ScalarSubtractionAssignmentModifiesVector)
{
  Vector4i vector(3, 4, 5, 6);

  vector -= 2;

  EXPECT_EQ(vector, Vector4i(1, 2, 3, 4));
}

TEST(Vector4Test, ScalarMultiplicationAssignmentModifiesVector)
{
  Vector4i vector(1, 2, 3, 4);

  vector *= 3;

  EXPECT_EQ(vector, Vector4i(3, 6, 9, 12));
}

TEST(Vector4Test, ScalarDivisionAssignmentModifiesVector)
{
  Vector4i vector(6, 12, 18, 24);

  vector /= 3;

  EXPECT_EQ(vector, Vector4i(2, 4, 6, 8));
}

// ============================================================================
// Equality
// ============================================================================

TEST(Vector4Test, EqualityReturnsTrueForEqualVectors)
{
  EXPECT_TRUE(
    Vector4i(1, 2, 3, 4) ==
    Vector4i(1, 2, 3, 4)
  );
}

TEST(Vector4Test, EqualityReturnsFalseWhenXDiffers)
{
  EXPECT_FALSE(
    Vector4i(1, 2, 3, 4) ==
    Vector4i(9, 2, 3, 4)
  );
}

TEST(Vector4Test, EqualityReturnsFalseWhenYDiffers)
{
  EXPECT_FALSE(
    Vector4i(1, 2, 3, 4) ==
    Vector4i(1, 9, 3, 4)
  );
}

TEST(Vector4Test, EqualityReturnsFalseWhenZDiffers)
{
  EXPECT_FALSE(
    Vector4i(1, 2, 3, 4) ==
    Vector4i(1, 2, 9, 4)
  );
}

TEST(Vector4Test, EqualityReturnsFalseWhenWDiffers)
{
  EXPECT_FALSE(
    Vector4i(1, 2, 3, 4) ==
    Vector4i(1, 2, 3, 9)
  );
}

TEST(Vector4Test, InequalityReturnsFalseForEqualVectors)
{
  EXPECT_FALSE(
    Vector4i(1, 2, 3, 4) !=
    Vector4i(1, 2, 3, 4)
  );
}

TEST(Vector4Test, InequalityReturnsTrueWhenComponentDiffers)
{
  EXPECT_TRUE(
    Vector4i(1, 2, 3, 4) !=
    Vector4i(1, 2, 3, 5)
  );
}

// ============================================================================
// Type Conversion
// ============================================================================

TEST(Vector4Test, IntegerVectorCanBeConvertedToFloatVector)
{
  const Vector4i source(1, 2, 3, 4);

  const Vector4f result =
    static_cast<Vector4f>(source);

  EXPECT_EQ(
    result,
    Vector4f(1.0f, 2.0f, 3.0f, 4.0f)
  );
}

TEST(Vector4Test, FloatVectorCanBeConvertedToIntegerVector)
{
  const Vector4f source(
    1.9f, -2.7f, 3.5f, -4.9f
  );

  const Vector4i result =
    static_cast<Vector4i>(source);

  EXPECT_EQ(
    result,
    Vector4i(1, -2, 3, -4)
  );
}

TEST(Vector4Test, IntegerVectorCanBeConvertedToDoubleVector)
{
  const Vector4i source(1, 2, 3, 4);

  const Vector4<f64> result =
    static_cast<Vector4<f64>>(source);

  EXPECT_DOUBLE_EQ(result.x, 1.0);
  EXPECT_DOUBLE_EQ(result.y, 2.0);
  EXPECT_DOUBLE_EQ(result.z, 3.0);
  EXPECT_DOUBLE_EQ(result.w, 4.0);
}

// ============================================================================
// To String
// ============================================================================

TEST(Vector4Test, ToStringReturnsExpectedFormat)
{
  const Vector4i vector(1, -2, 3, -4);

  EXPECT_EQ(
    vector.toString(),
    "{ x:1, y:-2, z:3, w:-4 }"
  );
}
#endif // NY_TEST_VECTOR4