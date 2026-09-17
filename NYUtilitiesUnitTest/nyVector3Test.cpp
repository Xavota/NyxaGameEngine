#include "pch.h"

#include "math/nyVector3.hpp"

using namespace nyEngineSDK;

namespace
{
  // Stores information about the most recent assertion.
  struct AssertCapture
  {
    bool triggered = false;
    const char* expression = nullptr;
    const char* file = nullptr;
    const char* message = nullptr;
    int line = 0;
  };

  AssertCapture gAssertCapture;


  // This function temporarily replaces Nyxa's normal assertion handler
  // during tests.
  //
  // Instead of breaking into the debugger or aborting the program,
  // it records the assertion information and returns.
  void testAssertHandler(
    const char* expr,
    const char* file,
    int line,
    const char* msg) noexcept
  {
    gAssertCapture.triggered = true;
    gAssertCapture.expression = expr;
    gAssertCapture.file = file;
    gAssertCapture.line = line;
    gAssertCapture.message = msg;
  }


  // Clears information from a previous assertion.
  void resetAssertCapture() noexcept
  {
    gAssertCapture = {};
  }


  // Temporarily installs an assertion handler.
  //
  // When this object goes out of scope, the previous Nyxa assertion
  // handler is automatically restored.
  class AssertHandlerGuard
  {
  public:
    explicit AssertHandlerGuard(AssertHandlerFn handler) noexcept
      : mPreviousHandler(getAssertHandler())
    {
      setAssertHandler(handler);
    }

    ~AssertHandlerGuard()
    {
      setAssertHandler(mPreviousHandler);
    }

    AssertHandlerGuard(const AssertHandlerGuard&) = delete;
    AssertHandlerGuard&
      operator=(const AssertHandlerGuard&) = delete;

  private:
    AssertHandlerFn mPreviousHandler;
  };

  constexpr f32 kTolerance = 1e-5f;

  // =========================================================================
  // Constructors
  // =========================================================================

  TEST(Vector3Test, DefaultConstructorInitializesToZero)
  {
    const Vector3f vector;

    EXPECT_FLOAT_EQ(vector.x, 0.0f);
    EXPECT_FLOAT_EQ(vector.y, 0.0f);
    EXPECT_FLOAT_EQ(vector.z, 0.0f);
  }

  TEST(Vector3Test, ComponentConstructorInitializesComponents)
  {
    const Vector3f vector(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(vector.x, 1.0f);
    EXPECT_FLOAT_EQ(vector.y, 2.0f);
    EXPECT_FLOAT_EQ(vector.z, 3.0f);
  }

  TEST(Vector3Test, DirectionScaleConstructorScalesVector)
  {
    const Vector3f direction(1.0f, 2.0f, 3.0f);
    const Vector3f vector(direction, 2.0f);

    EXPECT_FLOAT_EQ(vector.x, 2.0f);
    EXPECT_FLOAT_EQ(vector.y, 4.0f);
    EXPECT_FLOAT_EQ(vector.z, 6.0f);
  }

  // =========================================================================
  // Constants
  // =========================================================================

  TEST(Vector3Test, ZeroConstantIsCorrect)
  {
    EXPECT_EQ(Vector3f::kZERO, Vector3f(0.0f, 0.0f, 0.0f));
  }

  TEST(Vector3Test, RightConstantIsCorrect)
  {
    EXPECT_EQ(Vector3f::kRIGHT, Vector3f(1.0f, 0.0f, 0.0f));
  }

  TEST(Vector3Test, UpConstantIsCorrect)
  {
    EXPECT_EQ(Vector3f::kUP, Vector3f(0.0f, 1.0f, 0.0f));
  }

  TEST(Vector3Test, ForwardConstantIsCorrect)
  {
    EXPECT_EQ(Vector3f::kFORWARD, Vector3f(0.0f, 0.0f, 1.0f));
  }

  // =========================================================================
  // Indexing
  // =========================================================================

  TEST(Vector3Test, IndexOperatorReturnsCorrectComponents)
  {
    const Vector3i vector(10, 20, 30);

    EXPECT_EQ(vector[0], 10);
    EXPECT_EQ(vector[1], 20);
    EXPECT_EQ(vector[2], 30);
  }

  TEST(Vector3Test, IndexOperatorCanModifyComponents)
  {
    Vector3i vector(10, 20, 30);

    vector[0] = 100;
    vector[1] = 200;
    vector[2] = 300;

    EXPECT_EQ(vector.x, 100);
    EXPECT_EQ(vector.y, 200);
    EXPECT_EQ(vector.z, 300);
  }

  TEST(Vector3Test, ConstIndexOperatorReturnsConstComponents)
  {
    const Vector3i vector(10, 20, 30);

    const i32& x = vector[0];
    const i32& y = vector[1];
    const i32& z = vector[2];

    EXPECT_EQ(x, 10);
    EXPECT_EQ(y, 20);
    EXPECT_EQ(z, 30);
  }

  // =========================================================================
  // Dot Product
  // =========================================================================

  TEST(Vector3Test, DotProductReturnsExpectedValue)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(4.0f, 5.0f, 6.0f);

    // 1*4 + 2*5 + 3*6 = 32
    EXPECT_FLOAT_EQ(a.dot(b), 32.0f);
  }

  TEST(Vector3Test, DotProductOfPerpendicularVectorsIsZero)
  {
    EXPECT_FLOAT_EQ(
      Vector3f::kRIGHT.dot(Vector3f::kUP),
      0.0f
    );

    EXPECT_FLOAT_EQ(
      Vector3f::kRIGHT.dot(Vector3f::kFORWARD),
      0.0f
    );

    EXPECT_FLOAT_EQ(
      Vector3f::kUP.dot(Vector3f::kFORWARD),
      0.0f
    );
  }

  TEST(Vector3Test, DotProductCanUseDifferentResultType)
  {
    const Vector3i a(1, 2, 3);
    const Vector3i b(4, 5, 6);

    const f32 result = a.dot<f32>(b);

    EXPECT_FLOAT_EQ(result, 32.0f);
  }

  // =========================================================================
  // Cross Product
  // =========================================================================

  TEST(Vector3Test, RightCrossUpReturnsForward)
  {
    const Vector3f result =
      Vector3f::kRIGHT.cross(Vector3f::kUP);

    EXPECT_EQ(result, Vector3f::kFORWARD);
  }

  TEST(Vector3Test, UpCrossForwardReturnsRight)
  {
    const Vector3f result =
      Vector3f::kUP.cross(Vector3f::kFORWARD);

    EXPECT_EQ(result, Vector3f::kRIGHT);
  }

  TEST(Vector3Test, ForwardCrossRightReturnsUp)
  {
    const Vector3f result =
      Vector3f::kFORWARD.cross(Vector3f::kRIGHT);

    EXPECT_EQ(result, Vector3f::kUP);
  }

  TEST(Vector3Test, CrossProductIsAntiCommutative)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(4.0f, 5.0f, 6.0f);

    EXPECT_EQ(a.cross(b), -(b.cross(a)));
  }

  TEST(Vector3Test, CrossProductIsPerpendicularToBothVectors)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(4.0f, -2.0f, 1.0f);

    const Vector3f result = a.cross(b);

    EXPECT_NEAR(result.dot(a), 0.0f, kTolerance);
    EXPECT_NEAR(result.dot(b), 0.0f, kTolerance);
  }

  TEST(Vector3Test, CrossProductOfParallelVectorsIsZero)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(2.0f, 4.0f, 6.0f);

    EXPECT_EQ(a.cross(b), Vector3f::kZERO);
  }

  TEST(Vector3Test, CrossProductWithItselfIsZero)
  {
    const Vector3i vector(2, 3, 4);

    EXPECT_EQ(vector.cross(vector), Vector3i::kZERO);
  }

  // =========================================================================
  // Distance
  // =========================================================================

  TEST(Vector3Test, SquaredDistanceReturnsExpectedValue)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(4.0f, 6.0f, 15.0f);

    // 3^2 + 4^2 + 12^2 = 169
    EXPECT_FLOAT_EQ(a.getSqrDistance(b), 169.0f);
  }

  TEST(Vector3Test, DistanceReturnsExpectedValue)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(4.0f, 6.0f, 15.0f);

    EXPECT_FLOAT_EQ(a.getDistance(b), 13.0f);
  }

  TEST(Vector3Test, DistanceIsSymmetric)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(4.0f, 6.0f, 15.0f);

    EXPECT_FLOAT_EQ(
      a.getDistance(b),
      b.getDistance(a)
    );
  }

  TEST(Vector3Test, DistanceToSelfIsZero)
  {
    const Vector3f vector(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(
      vector.getDistance(vector),
      0.0f
    );
  }

  TEST(Vector3Test, IntegerDistanceDefaultsToFloat)
  {
    const Vector3i a(0, 0, 0);
    const Vector3i b(2, 3, 6);

    // sqrt(4 + 9 + 36) = 7
    const f32 distance = a.getDistance(b);

    EXPECT_FLOAT_EQ(distance, 7.0f);
  }

  // =========================================================================
  // Magnitude
  // =========================================================================

  TEST(Vector3Test, SquaredMagnitudeReturnsExpectedValue)
  {
    const Vector3f vector(2.0f, 3.0f, 6.0f);

    EXPECT_FLOAT_EQ(
      vector.getSqrMagnitude(),
      49.0f
    );
  }

  TEST(Vector3Test, MagnitudeReturnsExpectedValue)
  {
    const Vector3f vector(2.0f, 3.0f, 6.0f);

    EXPECT_FLOAT_EQ(
      vector.getMagnitude(),
      7.0f
    );
  }

  TEST(Vector3Test, ZeroVectorHasZeroMagnitude)
  {
    EXPECT_FLOAT_EQ(
      Vector3f::kZERO.getMagnitude(),
      0.0f
    );
  }

  TEST(Vector3Test, IntegerMagnitudeDefaultsToFloat)
  {
    const Vector3i vector(2, 3, 6);

    const f32 magnitude = vector.getMagnitude();

    EXPECT_FLOAT_EQ(magnitude, 7.0f);
  }

  // =========================================================================
  // Normalization
  // =========================================================================

  TEST(Vector3Test, GetNormalizedReturnsUnitVector)
  {
    const Vector3f vector(2.0f, 3.0f, 6.0f);

    const Vector3f result = vector.getNormalized();

    EXPECT_NEAR(result.getMagnitude(), 1.0f, kTolerance);
  }

  TEST(Vector3Test, GetNormalizedPreservesDirection)
  {
    const Vector3f vector(2.0f, 3.0f, 6.0f);

    const Vector3f result = vector.getNormalized();

    EXPECT_NEAR(result.x, 2.0f / 7.0f, kTolerance);
    EXPECT_NEAR(result.y, 3.0f / 7.0f, kTolerance);
    EXPECT_NEAR(result.z, 6.0f / 7.0f, kTolerance);
  }

  TEST(Vector3Test, GetNormalizedDoesNotModifyOriginalVector)
  {
    const Vector3f vector(2.0f, 3.0f, 6.0f);

    const Vector3f result = vector.getNormalized();

    EXPECT_EQ(vector, Vector3f(2.0f, 3.0f, 6.0f));
    EXPECT_NEAR(result.getMagnitude(), 1.0f, kTolerance);
  }

  TEST(Vector3Test, NormalizeModifiesOriginalVector)
  {
    Vector3f vector(2.0f, 3.0f, 6.0f);

    vector.normalize();

    EXPECT_NEAR(vector.getMagnitude(), 1.0f, kTolerance);
    EXPECT_NEAR(vector.x, 2.0f / 7.0f, kTolerance);
    EXPECT_NEAR(vector.y, 3.0f / 7.0f, kTolerance);
    EXPECT_NEAR(vector.z, 6.0f / 7.0f, kTolerance);
  }

  TEST(Vector3Test, NormalizeReturnsNormalizedVector)
  {
    Vector3f vector(2.0f, 3.0f, 6.0f);

    const Vector3f result = vector.normalize();

    EXPECT_EQ(result, vector);
    EXPECT_NEAR(result.getMagnitude(), 1.0f, kTolerance);
  }

  TEST(Vector3Test, NormalizingZeroVectorReturnsZero)
  {
    const Vector3f result =
      Vector3f::kZERO.getNormalized();

    EXPECT_EQ(result, Vector3f::kZERO);
  }

  // =========================================================================
  // Truncation
  // =========================================================================

  TEST(Vector3Test, GetTruncatedReturnsRequestedMagnitude)
  {
    const Vector3f vector(2.0f, 3.0f, 6.0f);

    const Vector3f result =
      vector.getTruncated(14.0f);

    EXPECT_NEAR(result.getMagnitude(), 14.0f, kTolerance);

    EXPECT_NEAR(result.x, 4.0f, kTolerance);
    EXPECT_NEAR(result.y, 6.0f, kTolerance);
    EXPECT_NEAR(result.z, 12.0f, kTolerance);
  }

  TEST(Vector3Test, GetTruncatedDoesNotModifyOriginalVector)
  {
    const Vector3f vector(2.0f, 3.0f, 6.0f);

    const Vector3f result =
      vector.getTruncated(14.0f);

    EXPECT_EQ(vector, Vector3f(2.0f, 3.0f, 6.0f));
    EXPECT_NEAR(result.getMagnitude(), 14.0f, kTolerance);
  }

  TEST(Vector3Test, TruncateModifiesOriginalVector)
  {
    Vector3f vector(2.0f, 3.0f, 6.0f);

    vector.truncate(14.0f);

    EXPECT_NEAR(vector.getMagnitude(), 14.0f, kTolerance);
    EXPECT_NEAR(vector.x, 4.0f, kTolerance);
    EXPECT_NEAR(vector.y, 6.0f, kTolerance);
    EXPECT_NEAR(vector.z, 12.0f, kTolerance);
  }

  TEST(Vector3Test, GetTruncatedZeroVectorReturnsZero)
  {
    const Vector3f result =
      Vector3f::kZERO.getTruncated(10.0f);

    EXPECT_EQ(result, Vector3f::kZERO);
  }

  TEST(Vector3Test, IntegerGetTruncatedDefaultsToFloatVector)
  {
    const Vector3i vector(2, 3, 6);

    const Vector3f result =
      vector.getTruncated(14.0f);

    EXPECT_NEAR(result.x, 4.0f, kTolerance);
    EXPECT_NEAR(result.y, 6.0f, kTolerance);
    EXPECT_NEAR(result.z, 12.0f, kTolerance);

    EXPECT_NEAR(result.getMagnitude(), 14.0f, kTolerance);
  }

  // =========================================================================
  // Projection
  // =========================================================================

  TEST(Vector3Test, ProjectionOntoXAxisReturnsXComponent)
  {
    const Vector3f a(3.0f, 4.0f, 5.0f);
    const Vector3f b = Vector3f::kRIGHT;

    auto result = Vector3f::projection(a, b);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 3.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 0.0f, kTolerance);
    EXPECT_NEAR(result.value().z, 0.0f, kTolerance);
  }

  TEST(Vector3Test, ProjectionOntoYAxisReturnsYComponent)
  {
    const Vector3f a(3.0f, 4.0f, 5.0f);

    auto result =
      Vector3f::projection(a, Vector3f::kUP);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 0.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 4.0f, kTolerance);
    EXPECT_NEAR(result.value().z, 0.0f, kTolerance);
  }

  TEST(Vector3Test, ProjectionOntoZAxisReturnsZComponent)
  {
    const Vector3f a(3.0f, 4.0f, 5.0f);

    auto result =
      Vector3f::projection(a, Vector3f::kFORWARD);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 0.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 0.0f, kTolerance);
    EXPECT_NEAR(result.value().z, 5.0f, kTolerance);
  }

  TEST(Vector3Test, ProjectionOntoZeroVectorFails)
  {
    const Vector3f a(3.0f, 4.0f, 5.0f);

    auto result =
      Vector3f::projection(a, Vector3f::kZERO);

    EXPECT_FALSE(result);
  }

  TEST(Vector3Test, IntegerProjectionReturnsFloatVector)
  {
    const Vector3i a(1, 1, 0);
    const Vector3i b(2, 0, 0);

    auto result = Vector3i::projection(a, b);

    ASSERT_TRUE(result);

    const Vector3f projected = result.value();

    EXPECT_NEAR(projected.x, 1.0f, kTolerance);
    EXPECT_NEAR(projected.y, 0.0f, kTolerance);
    EXPECT_NEAR(projected.z, 0.0f, kTolerance);
  }

  // =========================================================================
  // Rejection
  // =========================================================================

  TEST(Vector3Test, RejectionRemovesProjectedComponent)
  {
    const Vector3f a(3.0f, 4.0f, 5.0f);

    auto result =
      Vector3f::rejection(a, Vector3f::kRIGHT);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 0.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 4.0f, kTolerance);
    EXPECT_NEAR(result.value().z, 5.0f, kTolerance);
  }

  TEST(Vector3Test, ProjectionPlusRejectionReconstructsOriginalVector)
  {
    const Vector3f a(3.0f, 4.0f, 5.0f);
    const Vector3f b(2.0f, 1.0f, 0.0f);

    auto projection =
      Vector3f::projection(a, b);

    auto rejection =
      Vector3f::rejection(a, b);

    ASSERT_TRUE(projection);
    ASSERT_TRUE(rejection);

    const Vector3f reconstructed =
      projection.value() + rejection.value();

    EXPECT_NEAR(reconstructed.x, a.x, kTolerance);
    EXPECT_NEAR(reconstructed.y, a.y, kTolerance);
    EXPECT_NEAR(reconstructed.z, a.z, kTolerance);
  }

  TEST(Vector3Test, RejectionOntoZeroVectorFails)
  {
    const Vector3f a(3.0f, 4.0f, 5.0f);

    auto result =
      Vector3f::rejection(a, Vector3f::kZERO);

    EXPECT_FALSE(result);
  }

  TEST(Vector3Test, IntegerRejectionReturnsFloatVector)
  {
    const Vector3i a(1, 1, 2);
    const Vector3i b(2, 0, 0);

    auto result = Vector3i::rejection(a, b);

    ASSERT_TRUE(result);

    const Vector3f rejected = result.value();

    EXPECT_NEAR(rejected.x, 0.0f, kTolerance);
    EXPECT_NEAR(rejected.y, 1.0f, kTolerance);
    EXPECT_NEAR(rejected.z, 2.0f, kTolerance);
  }

  // =========================================================================
  // Reflection
  // =========================================================================

  TEST(Vector3Test, ReflectionAcrossUpNormalFlipsYComponent)
  {
    const Vector3f vector(3.0f, -4.0f, 5.0f);

    auto result =
      Vector3f::reflection(vector, Vector3f::kUP);

    ASSERT_TRUE(result);

    EXPECT_NEAR(result.value().x, 3.0f, kTolerance);
    EXPECT_NEAR(result.value().y, 4.0f, kTolerance);
    EXPECT_NEAR(result.value().z, 5.0f, kTolerance);
  }

  TEST(Vector3Test, ReflectionPreservesMagnitude)
  {
    const Vector3f vector(3.0f, -4.0f, 5.0f);
    const Vector3f normal(1.0f, 2.0f, 0.0f);

    auto result =
      Vector3f::reflection(vector, normal);

    ASSERT_TRUE(result);

    EXPECT_NEAR(
      result.value().getMagnitude(),
      vector.getMagnitude(),
      kTolerance
    );
  }

  TEST(Vector3Test, ReflectionWithZeroNormalFails)
  {
    const Vector3f vector(3.0f, -4.0f, 5.0f);

    auto result =
      Vector3f::reflection(vector, Vector3f::kZERO);

    EXPECT_FALSE(result);
  }

  TEST(Vector3Test, IntegerReflectionReturnsFloatVector)
  {
    const Vector3i vector(3, -4, 5);
    const Vector3i normal(0, 2, 0);

    auto result =
      Vector3i::reflection(vector, normal);

    ASSERT_TRUE(result);

    const Vector3f reflected = result.value();

    EXPECT_NEAR(reflected.x, 3.0f, kTolerance);
    EXPECT_NEAR(reflected.y, 4.0f, kTolerance);
    EXPECT_NEAR(reflected.z, 5.0f, kTolerance);
  }

  // =========================================================================
  // Lerp
  // =========================================================================

  TEST(Vector3Test, LerpAtZeroReturnsStart)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(5.0f, 6.0f, 7.0f);

    const Vector3f result =
      Vector3f::lerp(a, b, 0.0f);

    EXPECT_EQ(result, a);
  }

  TEST(Vector3Test, LerpAtOneReturnsEnd)
  {
    const Vector3f a(1.0f, 2.0f, 3.0f);
    const Vector3f b(5.0f, 6.0f, 7.0f);

    const Vector3f result =
      Vector3f::lerp(a, b, 1.0f);

    EXPECT_EQ(result, b);
  }

  TEST(Vector3Test, LerpAtHalfReturnsMidpoint)
  {
    const Vector3f a(0.0f, 2.0f, 4.0f);
    const Vector3f b(10.0f, 6.0f, 8.0f);

    const Vector3f result =
      Vector3f::lerp(a, b, 0.5f);

    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
  }

  TEST(Vector3Test, IntegerLerpDefaultsToFloatVector)
  {
    const Vector3i a(0, 0, 0);
    const Vector3i b(10, 20, 30);

    const Vector3f result =
      Vector3i::lerp(a, b, 0.5f);

    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 10.0f);
    EXPECT_FLOAT_EQ(result.z, 15.0f);
  }

  TEST(Vector3Test, LerpWithCurveTransformsAlpha)
  {
    const Vector3f a(0.0f, 0.0f, 0.0f);
    const Vector3f b(10.0f, 20.0f, 30.0f);

    auto quadratic = [](f32 alpha) noexcept
    {
      return alpha * alpha;
    };

    // alpha = 0.5 -> curve alpha = 0.25
    const Vector3f result =
      Vector3f::lerp(a, b, 0.5f, quadratic);

    EXPECT_FLOAT_EQ(result.x, 2.5f);
    EXPECT_FLOAT_EQ(result.y, 5.0f);
    EXPECT_FLOAT_EQ(result.z, 7.5f);
  }

  // =========================================================================
  // Vector Arithmetic
  // =========================================================================

  TEST(Vector3Test, AdditionAddsComponents)
  {
    const Vector3i a(1, 2, 3);
    const Vector3i b(4, 5, 6);

    EXPECT_EQ(a + b, Vector3i(5, 7, 9));
  }

  TEST(Vector3Test, SubtractionSubtractsComponents)
  {
    const Vector3i a(5, 7, 9);
    const Vector3i b(4, 5, 6);

    EXPECT_EQ(a - b, Vector3i(1, 2, 3));
  }

  // =========================================================================
  // Scalar Arithmetic
  // =========================================================================

  TEST(Vector3Test, ScalarAdditionAddsToEveryComponent)
  {
    EXPECT_EQ(
      Vector3i(1, 2, 3) + 2,
      Vector3i(3, 4, 5)
    );
  }

  TEST(Vector3Test, ScalarSubtractionSubtractsFromEveryComponent)
  {
    EXPECT_EQ(
      Vector3i(3, 4, 5) - 2,
      Vector3i(1, 2, 3)
    );
  }

  TEST(Vector3Test, ScalarMultiplicationMultipliesEveryComponent)
  {
    EXPECT_EQ(
      Vector3i(1, 2, 3) * 3,
      Vector3i(3, 6, 9)
    );
  }

  TEST(Vector3Test, ScalarDivisionDividesEveryComponent)
  {
    EXPECT_EQ(
      Vector3i(6, 12, 18) / 3,
      Vector3i(2, 4, 6)
    );
  }

  // =========================================================================
  // Unary Minus
  // =========================================================================

  TEST(Vector3Test, UnaryMinusNegatesEveryComponent)
  {
    const Vector3i vector(1, -2, 3);

    EXPECT_EQ(-vector, Vector3i(-1, 2, -3));
  }

  // =========================================================================
  // Compound Assignment
  // =========================================================================

  TEST(Vector3Test, VectorAdditionAssignmentModifiesVector)
  {
    Vector3i vector(1, 2, 3);

    vector += Vector3i(4, 5, 6);

    EXPECT_EQ(vector, Vector3i(5, 7, 9));
  }

  TEST(Vector3Test, VectorSubtractionAssignmentModifiesVector)
  {
    Vector3i vector(5, 7, 9);

    vector -= Vector3i(4, 5, 6);

    EXPECT_EQ(vector, Vector3i(1, 2, 3));
  }

  TEST(Vector3Test, ScalarAdditionAssignmentModifiesVector)
  {
    Vector3i vector(1, 2, 3);

    vector += 2;

    EXPECT_EQ(vector, Vector3i(3, 4, 5));
  }

  TEST(Vector3Test, ScalarSubtractionAssignmentModifiesVector)
  {
    Vector3i vector(3, 4, 5);

    vector -= 2;

    EXPECT_EQ(vector, Vector3i(1, 2, 3));
  }

  TEST(Vector3Test, ScalarMultiplicationAssignmentModifiesVector)
  {
    Vector3i vector(1, 2, 3);

    vector *= 3;

    EXPECT_EQ(vector, Vector3i(3, 6, 9));
  }

  TEST(Vector3Test, ScalarDivisionAssignmentModifiesVector)
  {
    Vector3i vector(6, 12, 18);

    vector /= 3;

    EXPECT_EQ(vector, Vector3i(2, 4, 6));
  }

  // =========================================================================
  // Equality
  // =========================================================================

  TEST(Vector3Test, EqualityReturnsTrueForEqualVectors)
  {
    EXPECT_TRUE(
      Vector3i(1, 2, 3) == Vector3i(1, 2, 3)
    );
  }

  TEST(Vector3Test, EqualityReturnsFalseWhenAnyComponentDiffers)
  {
    EXPECT_FALSE(
      Vector3i(1, 2, 3) == Vector3i(1, 2, 4)
    );
  }

  TEST(Vector3Test, InequalityReturnsFalseForEqualVectors)
  {
    EXPECT_FALSE(
      Vector3i(1, 2, 3) != Vector3i(1, 2, 3)
    );
  }

  TEST(Vector3Test, InequalityReturnsTrueWhenAnyComponentDiffers)
  {
    EXPECT_TRUE(
      Vector3i(1, 2, 3) != Vector3i(1, 5, 3)
    );
  }

  // =========================================================================
  // Type Conversion
  // =========================================================================

  TEST(Vector3Test, IntegerVectorCanBeConvertedToFloatVector)
  {
    const Vector3i source(1, 2, 3);

    const Vector3f result =
      static_cast<Vector3f>(source);

    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
  }

  TEST(Vector3Test, FloatVectorCanBeConvertedToIntegerVector)
  {
    const Vector3f source(1.9f, -2.7f, 3.5f);

    const Vector3i result =
      static_cast<Vector3i>(source);

    EXPECT_EQ(result.x, 1);
    EXPECT_EQ(result.y, -2);
    EXPECT_EQ(result.z, 3);
  }

  // =========================================================================
  // To String
  // =========================================================================

  TEST(Vector3Test, ToStringReturnsExpectedFormat)
  {
    const Vector3i vector(1, -2, 3);

    EXPECT_EQ(
      vector.toString(),
      "{ x:1, y:-2, z:3 }"
    );
  }

  TEST(Vector3Test, IndexOperatorAssertsWhenIndexIsOutOfBounds)
  {
#if NY_ENABLE_ASSERTS
    resetAssertCapture();

    AssertHandlerGuard guard(&testAssertHandler);

    Vector3i vector(10, 20, 30);

    NY_MAYBE_UNUSED i32 value = vector[3];

    EXPECT_TRUE(gAssertCapture.triggered);
    EXPECT_STREQ(gAssertCapture.expression, "index < 3");
    EXPECT_GT(gAssertCapture.line, 0);
#endif
  }
  
  TEST(Vector3Test, ConstIndexOperatorAssertsWhenIndexIsOutOfBounds)
  {
#if NY_ENABLE_ASSERTS
    resetAssertCapture();

    AssertHandlerGuard guard(&testAssertHandler);

    const Vector3i vector(10, 20, 30);

    NY_MAYBE_UNUSED i32 value = vector[3];

    EXPECT_TRUE(gAssertCapture.triggered);
    EXPECT_STREQ(gAssertCapture.expression, "index < 3");
    EXPECT_GT(gAssertCapture.line, 0);
#endif
  }
}