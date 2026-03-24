/******************************************************************************/
/**
 * @file    nyTime.hpp
 * @author  Dalia Castellanos
 * @date    05/03/2026
 * @brief   Defines the Time class for time-related utilities.
 * 
 * Defines a `Time` class that provides static utility functions for working with
 * time, such as getting the current time and sleeping for a specified duration.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <chrono>
#include <thread>

#include "types/nyTypes.hpp"

namespace nyEngineSDK
{
  /**
   * @brief Time utilities based on a monotonic clock.
   * @bug No known bugs
   */
  class Time
  {
   public:
    /**
     * @brief Returns a monotonic timestamp in a Duration object.
     * @bug No known bugs
     */
    static Duration
    now() noexcept
    {
      auto now = std::chrono::steady_clock::now().time_since_epoch();
      u64 nanoseconds = static_cast<u64>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
      return Duration(0, 0, 0, 0, 0, 0, static_cast<u64>(nanoseconds));
    }

    /**
     * @brief Sleeps the current thread for the given time.
     * @bug No known bugs
     */
    static void
    sleep(Duration t) noexcept
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(t.getNanoseconds()));
    }
  };
} // namespace nyEngineSDK