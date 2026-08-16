#include "tools/nyTime.h"

namespace nyEngineSDK
{
  const Duration Time::fixedDeltaTime = Duration::fromSecondsF(0.02f);

  void
  Time::update(Duration timeElapsed)
  {
    deltaTime = timeElapsed * static_cast<f64>(deltaTimeScale);
    currentTime += deltaTime;
  }
}