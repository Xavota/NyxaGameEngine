/*****************************************************************************/
/**
 * @file    nySpinlock.hpp
 * @author  Dalia Castellanos
 * @date    03/03/2026
 * @brief   Defines a simple spin lock for the Utilities library.
 * 
 * Defines a simple `SpinLock` class that provides basic locking functionality
 * using an atomic flag to indicate whether the lock is held. The `SpinLock`
 * is designed for very short critical sections where the overhead of a mutex
 * may be too high, but it should be used with caution to avoid excessive
 * spinning and CPU contention.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include <atomic>
#include <thread>

#include "u0/nyMacros.hpp"

namespace nyEngineSDK
{
  /**
   * @brief A simple spin lock for very short critical sections.
   * @bug No known bugs
   */
  class SpinLock
  {
   public:
    /**
     * @brief Constructs an unlocked SpinLock.
     * @bug No known bugs
     */
    SpinLock() noexcept
      : mFlag()
    {
      mFlag.clear(std::memory_order_relaxed);
    }

    /**
     * @brief Deleted copy constructor to prevent copying of the SpinLock.
     * @bug No known bugs
     */
    SpinLock(const SpinLock&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying of the SpinLock.
     * @bug No known bugs
     */
    SpinLock&
    operator=(const SpinLock&) = delete;

    /**
     * @brief Acquires the lock, spinning until it becomes available.
     * @bug No known bugs
     */
    void
    lock() noexcept
    {
      for (;;)
      {
        if (!mFlag.test_and_set(std::memory_order_acquire))
        {
          return;
        }

        // Simple backoff: yield to reduce contention.
        std::this_thread::yield();
      }
    }

    /**
     * @brief Attempts to acquire the lock without blocking.
     * @bug No known bugs
     */
    bool
    tryLock() noexcept
    {
      return !mFlag.test_and_set(std::memory_order_acquire);
    }

    /**
     * @brief Releases the lock.
     * @bug No known bugs
     */
    void
    unlock() noexcept
    {
      mFlag.clear(std::memory_order_release);
    }

   private:
    /**
     * @brief The atomic flag used to indicate whether the lock is held.
     *        A value of `false` indicates that the lock is available,
     *        while `true` indicates that the lock is held by some thread.
     */
    std::atomic_flag mFlag;
  };
} // namespace nyEngineSDK