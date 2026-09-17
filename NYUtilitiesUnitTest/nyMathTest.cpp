#include "pch.h"

#include "math/nyMath.h"

using namespace nyEngineSDK;

namespace
{
  constexpr f32 kTolerance = 1e-5f;

  // =========================================================================
  // Constants
  // =========================================================================

  TEST(MathTest, PiConstantsHaveExpectedValues)
  {
    EXPECT_NEAR(Math::kPi<f32>, 3.14159265f, kTolerance);
    EXPECT_NEAR(Math::kPi<f64>, 3.141592653589793, 1e-14);
    EXPECT_NEAR(
      static_cast<f64>(Math::kPi<f64L>),
      3.141592653589793,
      1e-14
    );
  }

  TEST(MathTest, PiDerivedConstantsAreCorrect)
  {
    EXPECT_NEAR(Math::kPiOver180<f32>,
                Math::kPi<f32> / 180.0f,
                kTolerance);

    EXPECT_NEAR(Math::k180OverPi<f32>,
                180.0f / Math::kPi<f32>,
                kTolerance);

    EXPECT_NEAR(Math::k2Pi<f32>,
                Math::kPi<f32> * 2.0f,
                kTolerance);

    EXPECT_NEAR(Math::kPiOver2<f32>,
                Math::kPi<f32> / 2.0f,
                kTolerance);

    EXPECT_NEAR(Math::kPiOver4<f32>,
                Math::kPi<f32> / 4.0f,
                kTolerance);
  }

  TEST(MathTest, EulerConstantsHaveExpectedValues)
  {
    EXPECT_NEAR(Math::kEulerNumber<f32>,
                2.718281828f,
                kTolerance);

    EXPECT_NEAR(Math::kEulerNumber<f64>,
                2.718281828459045,
                1e-14);
  }

  TEST(MathTest, TypedToleranceConstantsMatchExpectedConstants)
  {
    EXPECT_EQ(Math::kSmallFloat<f32>, Math::kFLOAT_SMALL);
    EXPECT_EQ(Math::kSmallFloat<f64>, Math::kFLOAT_SMALLd);
    EXPECT_EQ(Math::kSmallFloat<f64L>, Math::kFLOAT_SMALLdL);

    EXPECT_EQ(Math::kTinyFloat<f32>, Math::kFLOAT_TINY);
    EXPECT_EQ(Math::kTinyFloat<f64>, Math::kFLOAT_TINYd);
    EXPECT_EQ(Math::kTinyFloat<f64L>, Math::kFLOAT_TINYdL);
  }

  TEST(MathTest, TypedFloatLimitsMatchExpectedConstants)
  {
    EXPECT_EQ(Math::kMaxFloat<f32>, Math::kMAX_FLOAT);
    EXPECT_EQ(Math::kMaxFloat<f64>, Math::kMAX_FLOATd);
    EXPECT_EQ(Math::kMaxFloat<f64L>, Math::kMAX_FLOATdL);

    EXPECT_EQ(Math::kMinFloat<f32>, Math::kMIN_FLOAT);
    EXPECT_EQ(Math::kMinFloat<f64>, Math::kMIN_FLOATd);
    EXPECT_EQ(Math::kMinFloat<f64L>, Math::kMIN_FLOATdL);
  }

  TEST(MathTest, TypedIntegerLimitsMatchExpectedConstants)
  {
    EXPECT_EQ(Math::kMinInt<i8>, Math::kMIN_INT_8);
    EXPECT_EQ(Math::kMinInt<i16>, Math::kMIN_INT_16);
    EXPECT_EQ(Math::kMinInt<i32>, Math::kMIN_INT_32);
    EXPECT_EQ(Math::kMinInt<i64>, Math::kMIN_INT_64);

    EXPECT_EQ(Math::kMaxInt<i8>, Math::kMAX_INT_8);
    EXPECT_EQ(Math::kMaxInt<i16>, Math::kMAX_INT_16);
    EXPECT_EQ(Math::kMaxInt<i32>, Math::kMAX_INT_32);
    EXPECT_EQ(Math::kMaxInt<i64>, Math::kMAX_INT_64);

    EXPECT_EQ(Math::kMaxUint<u8>, Math::kMAX_UINT_8);
    EXPECT_EQ(Math::kMaxUint<u16>, Math::kMAX_UINT_16);
    EXPECT_EQ(Math::kMaxUint<u32>, Math::kMAX_UINT_32);
    EXPECT_EQ(Math::kMaxUint<u64>, Math::kMAX_UINT_64);
  }

  // =========================================================================
  // Angle Conversion
  // =========================================================================

  TEST(MathTest, DegreesToRadiansConvertsCorrectly)
  {
    EXPECT_NEAR(Math::degToRad(0.0f),
                0.0f,
                kTolerance);

    EXPECT_NEAR(Math::degToRad(90.0f),
                Math::kPiOver2<f32>,
                kTolerance);

    EXPECT_NEAR(Math::degToRad(180.0f),
                Math::kPi<f32>,
                kTolerance);

    EXPECT_NEAR(Math::degToRad(360.0f),
                Math::k2Pi<f32>,
                kTolerance);
  }

  TEST(MathTest, RadiansToDegreesConvertsCorrectly)
  {
    EXPECT_NEAR(Math::radToDeg(0.0f),
                0.0f,
                kTolerance);

    EXPECT_NEAR(Math::radToDeg(Math::kPiOver2<f32>),
                90.0f,
                kTolerance);

    EXPECT_NEAR(Math::radToDeg(Math::kPi<f32>),
                180.0f,
                kTolerance);

    EXPECT_NEAR(Math::radToDeg(Math::k2Pi<f32>),
                360.0f,
                kTolerance);
  }

  TEST(MathTest, DegreeRadianConversionRoundTrip)
  {
    constexpr f32 original = 123.456f;

    const f32 result =
      Math::radToDeg(Math::degToRad(original));

    EXPECT_NEAR(result, original, kTolerance);
  }

  TEST(MathTest, DoubleAngleConversionsUseDoublePrecision)
  {
    const f64 radians = Math::degToRad(180.0);

    EXPECT_NEAR(radians, Math::kPId, 1e-14);

    const f64 degrees = Math::radToDeg(Math::kPId);

    EXPECT_NEAR(degrees, 180.0, 1e-12);
  }

  // =========================================================================
  // Degree Trigonometric Functions
  // =========================================================================

  TEST(MathTest, DegreeTrigFunctionsProduceExpectedValues)
  {
    EXPECT_NEAR(Math::sind(30.0f), 0.5f, kTolerance);
    EXPECT_NEAR(Math::cosd(60.0f), 0.5f, kTolerance);
    EXPECT_NEAR(Math::tand(45.0f), 1.0f, kTolerance);
  }

  // =========================================================================
  // Reciprocal Trigonometric Functions
  // =========================================================================

  TEST(MathTest, SecantReturnsReciprocalOfCosine)
  {
    EXPECT_NEAR(
      Math::sec(Math::kPi<f32> / 3.0f),
      2.0f,
      kTolerance
    );
  }

  TEST(MathTest, CosecantReturnsReciprocalOfSine)
  {
    EXPECT_NEAR(
      Math::csc(Math::kPi<f32> / 6.0f),
      2.0f,
      kTolerance
    );
  }

  TEST(MathTest, CotangentReturnsReciprocalOfTangent)
  {
    EXPECT_NEAR(
      Math::cot(Math::kPi<f32> / 4.0f),
      1.0f,
      kTolerance
    );
  }

  TEST(MathTest, DegreeReciprocalTrigFunctionsProduceExpectedValues)
  {
    EXPECT_NEAR(Math::secd(60.0f), 2.0f, kTolerance);
    EXPECT_NEAR(Math::cscd(30.0f), 2.0f, kTolerance);
    EXPECT_NEAR(Math::cotd(45.0f), 1.0f, kTolerance);
  }

  // =========================================================================
  // Inverse Reciprocal Trigonometric Functions
  // =========================================================================

  TEST(MathTest, ArcSecantProducesExpectedRadians)
  {
    EXPECT_NEAR(
      Math::asec(2.0f),
      Math::kPi<f32> / 3.0f,
      kTolerance
    );
  }

  TEST(MathTest, ArcCosecantProducesExpectedRadians)
  {
    EXPECT_NEAR(
      Math::acsc(2.0f),
      Math::kPi<f32> / 6.0f,
      kTolerance
    );
  }

  TEST(MathTest, ArcCotangentProducesExpectedRadians)
  {
    EXPECT_NEAR(
      Math::acot(1.0f),
      Math::kPiOver4<f32>,
      kTolerance
    );
  }

  // =========================================================================
  // Fraction
  // =========================================================================

  TEST(MathTest, FractionReturnsFractionalPartOfPositiveValue)
  {
    EXPECT_NEAR(Math::frac(3.75f),
                0.75f,
                kTolerance);
  }

  TEST(MathTest, FractionReturnsZeroForWholeValue)
  {
    EXPECT_NEAR(Math::frac(5.0f),
                0.0f,
                kTolerance);
  }

  TEST(MathTest, FractionPreservesSignForNegativeValue)
  {
    EXPECT_NEAR(Math::frac(-3.75f),
                -0.75f,
                kTolerance);
  }

  // =========================================================================
  // Square
  // =========================================================================

  TEST(MathTest, SquareReturnsValueSquared)
  {
    EXPECT_EQ(Math::sqr(4), 16);
    EXPECT_FLOAT_EQ(Math::sqr(3.0f), 9.0f);
  }

  TEST(MathTest, SquareOfNegativeValueIsPositive)
  {
    EXPECT_EQ(Math::sqr(-4), 16);
    EXPECT_FLOAT_EQ(Math::sqr(-3.0f), 9.0f);
  }

  TEST(MathTest, SquareOfZeroIsZero)
  {
    EXPECT_EQ(Math::sqr(0), 0);
  }

  // =========================================================================
  // Custom Base Logarithm
  // =========================================================================

  TEST(MathTest, CustomBaseLogarithmReturnsCorrectValue)
  {
    EXPECT_NEAR(Math::log(2.0f, 8.0f),
                3.0f,
                kTolerance);

    EXPECT_NEAR(Math::log(10.0f, 1000.0f),
                3.0f,
                kTolerance);
  }

  // =========================================================================
  // Linear Interpolation
  // =========================================================================

  TEST(MathTest, LerpAtZeroReturnsStart)
  {
    EXPECT_FLOAT_EQ(
      Math::lerp(10.0f, 20.0f, 0.0f),
      10.0f
    );
  }

  TEST(MathTest, LerpAtOneReturnsEnd)
  {
    EXPECT_FLOAT_EQ(
      Math::lerp(10.0f, 20.0f, 1.0f),
      20.0f
    );
  }

  TEST(MathTest, LerpAtHalfReturnsMidpoint)
  {
    EXPECT_FLOAT_EQ(
      Math::lerp(10.0f, 20.0f, 0.5f),
      15.0f
    );
  }

  TEST(MathTest, LerpWorksWithDescendingRange)
  {
    EXPECT_FLOAT_EQ(
      Math::lerp(20.0f, 10.0f, 0.25f),
      17.5f
    );
  }

  TEST(MathTest, LerpSupportsExtrapolation)
  {
    EXPECT_FLOAT_EQ(
      Math::lerp(10.0f, 20.0f, 1.5f),
      25.0f
    );

    EXPECT_FLOAT_EQ(
      Math::lerp(10.0f, 20.0f, -0.5f),
      5.0f
    );
  }

  TEST(MathTest, LerpSupportsIntegerValuesWithFloatAlpha)
  {
    EXPECT_EQ(
      Math::lerp(10, 20, 0.5f),
      15
    );
  }

  // =========================================================================
  // Lerp With Curve
  // =========================================================================

  TEST(MathTest, LerpWithLinearCurveMatchesNormalLerp)
  {
    auto linear = [](f32 t) noexcept
    {
      return t;
    };

    EXPECT_FLOAT_EQ(
      Math::lerp(10.0f, 20.0f, 0.25f, linear),
      Math::lerp(10.0f, 20.0f, 0.25f)
    );
  }

  TEST(MathTest, LerpWithQuadraticCurveTransformsAlpha)
  {
    auto quadratic = [](f32 t) noexcept
    {
      return t * t;
    };

    // 0.5^2 = 0.25
    // 10 + (20 - 10) * 0.25 = 12.5
    EXPECT_FLOAT_EQ(
      Math::lerp(10.0f, 20.0f, 0.5f, quadratic),
      12.5f
    );
  }

  TEST(MathTest, LerpCurveMayReturnConvertibleType)
  {
    auto curve = [](f32 t) noexcept -> f64
    {
      return static_cast<f64>(t * t);
    };

    EXPECT_NEAR(
      Math::lerp(0.0f, 100.0f, 0.5f, curve),
      25.0f,
      kTolerance
    );
  }

  // =========================================================================
  // Sign
  // =========================================================================

  TEST(MathTest, SignReturnsPositiveOneForPositiveValue)
  {
    EXPECT_FLOAT_EQ(Math::sign(5.0f), 1.0f);
  }

  TEST(MathTest, SignReturnsNegativeOneForNegativeValue)
  {
    EXPECT_FLOAT_EQ(Math::sign(-5.0f), -1.0f);
  }

  TEST(MathTest, SignTreatsZeroAsPositive)
  {
    EXPECT_FLOAT_EQ(Math::sign(0.0f), 1.0f);
  }

  TEST(MathTest, SignWorksWithIntegers)
  {
    EXPECT_EQ(Math::sign(42), 1);
    EXPECT_EQ(Math::sign(-42), -1);
    EXPECT_EQ(Math::sign(0), 1);
  }

  // =========================================================================
  // Copy Sign
  // =========================================================================

  TEST(MathTest, CopySignAppliesPositiveSign)
  {
    EXPECT_FLOAT_EQ(
      Math::copysign(-5.0f, 2.0f),
      5.0f
    );
  }

  TEST(MathTest, CopySignAppliesNegativeSign)
  {
    EXPECT_FLOAT_EQ(
      Math::copysign(5.0f, -2.0f),
      -5.0f
    );
  }

  TEST(MathTest, CopySignUsesMagnitudeOfFirstArgument)
  {
    EXPECT_FLOAT_EQ(
      Math::copysign(-5.0f, -2.0f),
      -5.0f
    );
  }

  // =========================================================================
  // Min / Max
  // =========================================================================

  TEST(MathTest, MaxReturnsLargerValue)
  {
    EXPECT_EQ(Math::max(10, 20), 20);
    EXPECT_EQ(Math::max(20, 10), 20);
  }

  TEST(MathTest, MinReturnsSmallerValue)
  {
    EXPECT_EQ(Math::min(10, 20), 10);
    EXPECT_EQ(Math::min(20, 10), 10);
  }

  TEST(MathTest, MinAndMaxHandleEqualValues)
  {
    EXPECT_EQ(Math::max(10, 10), 10);
    EXPECT_EQ(Math::min(10, 10), 10);
  }

  TEST(MathTest, MinAndMaxHandleNegativeValues)
  {
    EXPECT_EQ(Math::max(-10, -20), -10);
    EXPECT_EQ(Math::min(-10, -20), -20);
  }

  // =========================================================================
  // Flags
  // =========================================================================

  TEST(MathTest, HasFlagReturnsTrueWhenSingleFlagExists)
  {
    constexpr u32 value = 0b1010;
    constexpr u32 flag  = 0b0010;

    EXPECT_TRUE(Math::hasFlag(value, flag));
  }

  TEST(MathTest, HasFlagReturnsFalseWhenFlagDoesNotExist)
  {
    constexpr u32 value = 0b1010;
    constexpr u32 flag  = 0b0100;

    EXPECT_FALSE(Math::hasFlag(value, flag));
  }

  TEST(MathTest, HasFlagRequiresAllBitsOfFlag)
  {
    constexpr u32 value = 0b1010;

    EXPECT_TRUE(
      Math::hasFlag(value, static_cast<u32>(0b1010))
    );

    EXPECT_FALSE(
      Math::hasFlag(value, static_cast<u32>(0b1110))
    );
  }

  TEST(MathTest, HasFlagReturnsTrueForZeroFlag)
  {
    constexpr u32 value = 0b1010;

    EXPECT_TRUE(
      Math::hasFlag(value, static_cast<u32>(0))
    );
  }

  // =========================================================================
  // Easing Functions
  // =========================================================================

  TEST(MathTest, LinearReturnsInput)
  {
    EXPECT_FLOAT_EQ(Math::linear(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(Math::linear(0.25f), 0.25f);
    EXPECT_FLOAT_EQ(Math::linear(0.5f), 0.5f);
    EXPECT_FLOAT_EQ(Math::linear(1.0f), 1.0f);
  }

  TEST(MathTest, EaseInQuadReturnsExpectedValues)
  {
    EXPECT_FLOAT_EQ(Math::easeInQuad(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(Math::easeInQuad(0.5f), 0.25f);
    EXPECT_FLOAT_EQ(Math::easeInQuad(1.0f), 1.0f);
  }

  TEST(MathTest, EaseOutQuadReturnsExpectedValues)
  {
    EXPECT_FLOAT_EQ(Math::easeOutQuad(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(Math::easeOutQuad(0.5f), 0.75f);
    EXPECT_FLOAT_EQ(Math::easeOutQuad(1.0f), 1.0f);
  }

  TEST(MathTest, SmoothStepReturnsExpectedValues)
  {
    EXPECT_FLOAT_EQ(Math::smoothStep(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(Math::smoothStep(0.5f), 0.5f);
    EXPECT_FLOAT_EQ(Math::smoothStep(1.0f), 1.0f);
  }

  TEST(MathTest, EasingFunctionsAreConstexpr)
  {
    constexpr f32 linear =
      Math::linear(0.5f);

    constexpr f32 easeIn =
      Math::easeInQuad(0.5f);

    constexpr f32 easeOut =
      Math::easeOutQuad(0.5f);

    constexpr f32 smooth =
      Math::smoothStep(0.5f);

    static_assert(linear == 0.5f);
    static_assert(easeIn == 0.25f);
    static_assert(easeOut == 0.75f);
    static_assert(smooth == 0.5f);

    SUCCEED();
  }
}