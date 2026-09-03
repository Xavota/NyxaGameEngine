#include "math/nyMath.h"

#include <limits>

namespace nyEngineSDK
{
  const float Math::kPI = Math::atan(1.0f) * 4.0f;
  const double Math::kPId = Math::atan(1.0) * 4.0;
  const long double Math::kPIdL = Math::atan(1.0l) * 4.0l;

  const float Math::kPI_OVER_180 = Math::kPI / 180.0f;
  const double Math::kPI_OVER_180d = Math::kPId / 180.0;
  const long double Math::kPI_OVER_180dL = Math::kPIdL / 180.0l;

  const float Math::k180_OVER_PI = 180.0f / Math::kPI;
  const double Math::k180_OVER_PId = 180.0 / Math::kPId;
  const long double Math::k180_OVER_PIdL = 180.0l / Math::kPIdL;

  const float Math::k2_PI = Math::kPI * 2.0f;
  const double Math::k2_PId = Math::kPId * 2.0;
  const long double Math::k2_PIdL = Math::kPIdL * 2.0l;

  const float Math::kPI_OVER_2 = Math::kPI / 2.0f;
  const double Math::kPI_OVER_2d = Math::kPId / 2.0;
  const long double Math::kPI_OVER_2dL = Math::kPIdL / 2.0l;

  const float Math::kPI_OVER_4 = Math::kPI / 4.0f;
  const double Math::kPI_OVER_4d = Math::kPId / 4.0;
  const long double Math::kPI_OVER_4dL = Math::kPIdL / 4.0l;

  const float Math::kEuler = Math::exp(1.0f);
  const double Math::kEulerd = Math::exp(1.0);
  const long double Math::kEulerdL = Math::exp(1.0l);


  const float Math::kFLOAT_SMALL = 1e-4f;
  const double Math::kFLOAT_SMALLd = 1e-8;
  const long double Math::kFLOAT_SMALLdL = 1e-10l;

  const float Math::kFLOAT_TINY = 1e-6f;
  const double Math::kFLOAT_TINYd = 1e-12;
  const long double Math::kFLOAT_TINYdL = 1e-15l;


  const float Math::kMAX_FLOAT = std::numeric_limits<float>::max();
  const double Math::kMAX_FLOATd = std::numeric_limits<double>::max();
  const long double Math::kMAX_FLOATdL = std::numeric_limits<long double>::max();

  const float Math::kMIN_FLOAT = std::numeric_limits<float>::lowest();
  const double Math::kMIN_FLOATd = std::numeric_limits<double>::lowest();
  const long double Math::kMIN_FLOATdL = std::numeric_limits<long double>::lowest();


  const i8 Math::kMIN_INT_8 = std::numeric_limits<i8>::min();
  const i16 Math::kMIN_INT_16 = std::numeric_limits<i16>::min();
  const i32 Math::kMIN_INT_32 = std::numeric_limits<i32>::min();
  const i64 Math::kMIN_INT_64 = std::numeric_limits<i64>::min();

  const i8 Math::kMAX_INT_8 = std::numeric_limits<i8>::max();
  const i16 Math::kMAX_INT_16 = std::numeric_limits<i16>::max();
  const i32 Math::kMAX_INT_32 = std::numeric_limits<i32>::max();
  const i64 Math::kMAX_INT_64 = std::numeric_limits<i64>::max();

  const u8 Math::kMAX_UINT_8 = std::numeric_limits<u8>::max();
  const u16 Math::kMAX_UINT_16 = std::numeric_limits<u16>::max();
  const u32 Math::kMAX_UINT_32 = std::numeric_limits<u32>::max();
  const u64 Math::kMAX_UINT_64 = std::numeric_limits<u64>::max();
}