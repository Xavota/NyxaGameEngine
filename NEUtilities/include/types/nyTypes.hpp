/******************************************************************************/
/**
 * @file    nyTypes.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines common type aliases for the Utilities library.
 *
 * Defines common type aliases for fixed-width integers, floating-point types,
 * and size types.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <cstdint>
#include <cstddef>

#include "macros/nyMacros.hpp"

namespace nyEngineSDK
{
  using i8 = std::int8_t;
  using i16 = std::int16_t;
  using i32 = std::int32_t;
  using i64 = std::int64_t;

  using u8 = std::uint8_t;
  using u16 = std::uint16_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  using byte = u8;

  using f32 = float;
  using f64 = double;

  using usize = std::size_t;
  using isize = std::ptrdiff_t;

  /**
   * @brief  A struct representing a duration of time, with fields for days,
   *         hours, minutes, seconds, milliseconds, microseconds, and nanoseconds.
   */
  struct Duration
  {
    /**
     * @brief  Constructs a Duration with all fields initialized to zero.
     * @bug    No known bugs
     */
    Duration() noexcept
      : days(0), hours(0), minutes(0), seconds(0),
      milliseconds(0), microseconds(0), nanoseconds(0) {}

    /**
     * @brief  Constructs a Duration with the specified values for each field.
     * @param  d   The number of days in the duration.
     * @param  h   The number of hours in the duration.
     * @param  m   The number of minutes in the duration.
     * @param  s   The number of seconds in the duration.
     * @param  ms  The number of milliseconds in the duration.
     * @param  us  The number of microseconds in the duration.
     * @param  ns  The number of nanoseconds in the duration.
     * @bug    No known bugs
     */
    Duration(u64 d, u64 h, u64 m, u64 s, u64 ms, u64 us, u64 ns) noexcept;

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in days.
     */
    u64 getDays() const noexcept
    {
      u64 totalDays = static_cast<u64>(days);
      totalDays += static_cast<u64>(hours / hoursPerDay);
      totalDays += static_cast<u64>(minutes / minutesPerDay);
      totalDays += static_cast<u64>(seconds / secondsPerDay);
      totalDays += static_cast<u64>(milliseconds / millisecondsPerDay);
      totalDays += static_cast<u64>(microseconds / microsecondsPerDay);
      totalDays += static_cast<u64>(nanoseconds / nanosecondsPerDay);
      return totalDays;
    }

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in hours.
     */
    u64 getHours() const noexcept
    {
      u64 totalHours = static_cast<u64>(hours);
      totalHours += static_cast<u64>(days * hoursPerDay);
      totalHours += static_cast<u64>(minutes / minutesPerHour);
      totalHours += static_cast<u64>(seconds / secondsPerHour);
      totalHours += static_cast<u64>(milliseconds / millisecondsPerHour);
      totalHours += static_cast<u64>(microseconds / microsecondsPerHour);
      totalHours += static_cast<u64>(nanoseconds / nanosecondsPerHour);
      return totalHours;
    }

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in minutes.
     */
    u64 getMinutes() const noexcept
    {
      u64 totalMinutes = static_cast<u64>(minutes);
      totalMinutes += static_cast<u64>(days * minutesPerDay);
      totalMinutes += static_cast<u64>(hours * minutesPerHour);
      totalMinutes += static_cast<u64>(seconds / secondsPerMinute);
      totalMinutes += static_cast<u64>(milliseconds / millisecondsPerMinute);
      totalMinutes += static_cast<u64>(microseconds / microsecondsPerMinute);
      totalMinutes += static_cast<u64>(nanoseconds / nanosecondsPerMinute);
      return totalMinutes;
    }

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in seconds.
     */
    u64 getSeconds() const noexcept
    {
      u64 totalSeconds = static_cast<u64>(seconds);
      totalSeconds += static_cast<u64>(days * secondsPerDay);
      totalSeconds += static_cast<u64>(hours * secondsPerHour);
      totalSeconds += static_cast<u64>(minutes * secondsPerMinute);
      totalSeconds += static_cast<u64>(milliseconds / millisecondsPerSecond);
      totalSeconds += static_cast<u64>(microseconds / microsecondsPerSecond);
      totalSeconds += static_cast<u64>(nanoseconds / nanosecondsPerSecond);
      return totalSeconds;
    }

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in milliseconds.
     */
    u64 getMilliseconds() const noexcept
    {
      u64 totalMilliseconds = static_cast<u64>(milliseconds);
      totalMilliseconds += static_cast<u64>(days * millisecondsPerDay);
      totalMilliseconds += static_cast<u64>(hours * millisecondsPerHour);
      totalMilliseconds += static_cast<u64>(minutes * millisecondsPerMinute);
      totalMilliseconds += static_cast<u64>(seconds * millisecondsPerSecond);
      totalMilliseconds += static_cast<u64>(microseconds / microsecondsPerMillisecond);
      totalMilliseconds += static_cast<u64>(nanoseconds / nanosecondsPerMillisecond);
      return totalMilliseconds;
    }

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in microseconds.
     */
    u64 getMicroseconds() const noexcept
    {
      u64 totalMicroseconds = static_cast<u64>(microseconds);
      totalMicroseconds += static_cast<u64>(days * microsecondsPerDay);
      totalMicroseconds += static_cast<u64>(hours * microsecondsPerHour);
      totalMicroseconds += static_cast<u64>(minutes * microsecondsPerMinute);
      totalMicroseconds += static_cast<u64>(seconds * microsecondsPerSecond);
      totalMicroseconds += static_cast<u64>(milliseconds * microsecondsPerMillisecond);
      totalMicroseconds += static_cast<u64>(nanoseconds / nanosecondsPerMicrosecond);
      return totalMicroseconds;
    }

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in nanoseconds.
     */
    u64 getNanoseconds() const noexcept
    {
      u64 totalNanoseconds = static_cast<u64>(nanoseconds);
      totalNanoseconds += static_cast<u64>(days * nanosecondsPerDay);
      totalNanoseconds += static_cast<u64>(hours * nanosecondsPerHour);
      totalNanoseconds += static_cast<u64>(minutes * nanosecondsPerMinute);
      totalNanoseconds += static_cast<u64>(seconds * nanosecondsPerSecond);
      totalNanoseconds += static_cast<u64>(milliseconds * nanosecondsPerMillisecond);
      totalNanoseconds += static_cast<u64>(microseconds * nanosecondsPerMicrosecond);
      return totalNanoseconds;
    }


    static u64 hoursPerDay;
    static u64 minutesPerDay;
    static u64 secondsPerDay;
    static u64 millisecondsPerDay;
    static u64 microsecondsPerDay;
    static u64 nanosecondsPerDay;

    static u64 minutesPerHour;
    static u64 secondsPerHour;
    static u64 millisecondsPerHour;
    static u64 microsecondsPerHour;
    static u64 nanosecondsPerHour;

    static u64 secondsPerMinute;
    static u64 millisecondsPerMinute;
    static u64 microsecondsPerMinute;
    static u64 nanosecondsPerMinute;

    static u64 millisecondsPerSecond;
    static u64 microsecondsPerSecond;
    static u64 nanosecondsPerSecond;

    static u64 microsecondsPerMillisecond;
    static u64 nanosecondsPerMillisecond;

    static u64 nanosecondsPerMicrosecond;

    u32 days;
    u32 hours;
    u32 minutes;
    u32 seconds;
    u32 milliseconds;
    u32 microseconds;
    u32 nanoseconds;
  };
} // namespace nyEngineSDK