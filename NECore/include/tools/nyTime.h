#pragma once

#include <macros/nyApi.hpp>
#include <types/nyTypes.hpp>

namespace nyEngineSDK
{
  class NY_API Time
  {
   public:
    Time() = default;
    ~Time() = default;
    
    static const Duration&
    getDeltatime() noexcept { return deltaTime; }
    static const Duration&
    getFixedDeltatime() noexcept { return fixedDeltaTime; }

    static f32
    getDeltatimeScale() noexcept { return deltaTimeScale; }
    static void
    setDeltatimeScale(f32 scale) noexcept { deltaTimeScale = scale; }

   private:
    friend class BaseApp;

    static void
    update(Duration timeElapsed);

    static Duration currentTime;
    static Duration deltaTime;
    static const Duration fixedDeltaTime;
    static f32 deltaTimeScale;
  };
}