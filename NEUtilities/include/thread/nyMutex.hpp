/*****************************************************************************/
/**
 * @file    nyMutex.hpp
 * @author  Dalia Castellanos
 * @date    03/03/2026
 * @brief   Defines the Mutex class for thread synchronization.
 * 
 * Defines a simple `Mutex` class that provides basic thread synchronization
 * functionality by wrapping `std::mutex`.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#if NY_COMPILER_MSVC
  #include <sal.h>
#endif
#include <mutex>

#include "macros/nyCompiler.hpp"

namespace nyEngineSDK
{
  /**
   * @brief Thin wrapper over std::mutex for engine-wide consistency.
   * @bug No known bugs
   */
  class Mutex
  {
   public:
    /**
     * @brief Constructs an unlocked mutex.
     * @bug No known bugs
     */
    Mutex() noexcept = default;

    /**
     * @brief Deleted copy constructor to prevent copying of the mutex.
     */
    Mutex(const Mutex&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying of the mutex.
     */
    Mutex&
    operator=(const Mutex&) = delete;

    /**
     * @brief Locks the mutex, blocking the calling thread until acquired.
     * @bug No known bugs
     */
    #if NY_COMPILER_MSVC
      _Acquires_lock_(mMutex)
    #endif
    void
    lock() noexcept
    {
      mMutex.lock();
    }

    /**
     * @brief Attempts to lock the mutex without blocking.
     * @bug No known bugs
     */
    bool
    tryLock() noexcept
    {
      return mMutex.try_lock();
    }

    /**
     * @brief Unlocks the mutex.
     * @bug No known bugs
     */
    #if NY_COMPILER_MSVC
      _Releases_lock_(mMutex)
    #endif
    void
    unlock() noexcept
    {
      mMutex.unlock();
    }

   private:
    friend class ConditionVariable;

    /**
     * @brief The underlying mutex object used for synchronization.
     */
    std::mutex mMutex;
  };
} // namespace nyEngineSDK