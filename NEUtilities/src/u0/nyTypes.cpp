#include "types/nyTypes.hpp"

namespace nyEngineSDK
{
  NY_STATIC_ASSERT(sizeof(i8)   == 1, "i8 must be 1 byte");
  NY_STATIC_ASSERT(sizeof(i16)  == 2, "i16 must be 2 bytes");
  NY_STATIC_ASSERT(sizeof(i32)  == 4, "i32 must be 4 bytes");
  NY_STATIC_ASSERT(sizeof(i64)  == 8, "i64 must be 8 bytes");

  NY_STATIC_ASSERT(sizeof(u8)   == 1, "u8 must be 1 byte");
  NY_STATIC_ASSERT(sizeof(u16)  == 2, "u16 must be 2 bytes");
  NY_STATIC_ASSERT(sizeof(u32)  == 4, "u32 must be 4 bytes");
  NY_STATIC_ASSERT(sizeof(u64)  == 8, "u64 must be 8 bytes");

  NY_STATIC_ASSERT(sizeof(byte) == 1, "byte must be 1 byte");

  NY_STATIC_ASSERT(sizeof(f32)  == 4, "f32 must be 4 bytes");
  NY_STATIC_ASSERT(sizeof(f64)  == 8, "f64 must be 8 bytes");

  u64 Duration::hoursPerDay = 24;
  u64 Duration::minutesPerDay = 1440;
  u64 Duration::secondsPerDay = 86400;
  u64 Duration::millisecondsPerDay = 86400000;
  u64 Duration::microsecondsPerDay = 86400000000;
  u64 Duration::nanosecondsPerDay = 86400000000000;

  u64 Duration::minutesPerHour = 60;
  u64 Duration::secondsPerHour = 3600;
  u64 Duration::millisecondsPerHour = 3600000;
  u64 Duration::microsecondsPerHour = 3600000000;
  u64 Duration::nanosecondsPerHour = 3600000000000;

  u64 Duration::secondsPerMinute = 60;
  u64 Duration::millisecondsPerMinute = 60000;
  u64 Duration::microsecondsPerMinute = 60000000;
  u64 Duration::nanosecondsPerMinute = 600000000000;

  u64 Duration::millisecondsPerSecond = 1000;
  u64 Duration::microsecondsPerSecond = 1000000;
  u64 Duration::nanosecondsPerSecond = 1000000000;

  u64 Duration::microsecondsPerMillisecond = 1000;
  u64 Duration::nanosecondsPerMillisecond = 1000000;

  u64 Duration::nanosecondsPerMicrosecond = 1000;

  Duration::Duration(u64 d, u64 h, u64 m, u64 s, u64 ms, u64 us, u64 ns) noexcept
  {
    days = static_cast<u32>(d);
    days += static_cast<u32>(h / hoursPerDay);
    days += static_cast<u32>(m / minutesPerDay);
    days += static_cast<u32>(s / secondsPerDay);
    days += static_cast<u32>(ms / millisecondsPerDay);
    days += static_cast<u32>(us / microsecondsPerDay);
    days += static_cast<u32>(ns / nanosecondsPerDay);

    h = h % hoursPerDay;
    m = m % minutesPerDay;
    s = s % secondsPerDay;
    ms = ms % millisecondsPerDay;
    us = us % microsecondsPerDay;
    ns = ns % nanosecondsPerDay;

    hours = static_cast<u32>(h);
    hours += static_cast<u32>(m / minutesPerHour);
    hours += static_cast<u32>(s / secondsPerHour);
    hours += static_cast<u32>(ms / millisecondsPerHour);
    hours += static_cast<u32>(us / microsecondsPerHour);
    hours += static_cast<u32>(ns / nanosecondsPerHour);

    m = m % minutesPerHour;
    s = s % secondsPerHour;
    ms = ms % millisecondsPerHour;
    us = us % microsecondsPerHour;
    ns = ns % nanosecondsPerHour;

    minutes = static_cast<u32>(m);
    minutes += static_cast<u32>(s / secondsPerMinute);
    minutes += static_cast<u32>(ms / millisecondsPerMinute);
    minutes += static_cast<u32>(us / microsecondsPerMinute);
    minutes += static_cast<u32>(ns / nanosecondsPerMinute);

    s = s % secondsPerMinute;
    ms = ms % millisecondsPerMinute;
    us = us % microsecondsPerMinute;
    ns = ns % nanosecondsPerMinute;

    seconds = static_cast<u32>(s);
    minutes += static_cast<u32>(ms / millisecondsPerSecond);
    minutes += static_cast<u32>(us / microsecondsPerSecond);
    minutes += static_cast<u32>(ns / nanosecondsPerSecond);

    ms = ms % millisecondsPerSecond;
    us = us % microsecondsPerSecond;
    ns = ns % nanosecondsPerSecond;

    milliseconds = static_cast<u32>(ms);
    minutes += static_cast<u32>(us / microsecondsPerMillisecond);
    minutes += static_cast<u32>(ns / nanosecondsPerMillisecond);

    us = us % microsecondsPerMillisecond;
    ns = ns % nanosecondsPerMillisecond;

    microseconds = static_cast<u32>(us);
    minutes += static_cast<u32>(ns / nanosecondsPerMicrosecond);

    ns = ns % nanosecondsPerMicrosecond;

    nanoseconds = static_cast<u32>(ns);
  }
}