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
     * @brief  Returns a normalized version of this Duration, where all of its
     *         values are as big as their maximum allows to, making all excess
     *         go up in the hierarchy.
     * @bug    No known bugs
     */
    Duration NY_FORCE_INLINE
    normalized() const noexcept
    {
      return Duration(days, hours, minutes, seconds, milliseconds, microseconds, nanoseconds);
    }

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in days.
     * @bug    No known bugs
     */
    u64
    getDays() const noexcept;

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in hours.
     * @bug    No known bugs
     */
    u64
    getHours() const noexcept;

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in minutes.
     * @bug    No known bugs
     */
    u64
    getMinutes() const noexcept;

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in seconds.
     * @bug    No known bugs
     */
    u64
    getSeconds() const noexcept;

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in milliseconds.
     * @bug    No known bugs
     */
    u64
    getMilliseconds() const noexcept;

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in microseconds.
     * @bug    No known bugs
     */
    u64
    getMicroseconds() const noexcept;

    /**
     * @brief  Returns the total duration represented by this `Duration` struct in nanoseconds.
     * @bug    No known bugs
     */
    u64
    getNanoseconds() const noexcept;

    /**
     * @brief  Checks if the total time in nanoseconds is the same for both Durations.
     *         Note: Careful for incorrect checks due to nanoseconds overflow
     *         above 213,503 days.
     * @bug    No known bugs
     */
    bool
    operator==(const Duration& other) const noexcept;

    /**
     * @brief  Checks if the total time in nanoseconds is different for both Durations.
     *         Note: Careful for incorrect checks due to nanoseconds overflow
     *         above 213,503 days.
     * @bug    No known bugs
     */
    bool
    operator!=(const Duration& other) const noexcept;


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