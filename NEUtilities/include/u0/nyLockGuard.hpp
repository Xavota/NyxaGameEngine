/******************************************************************************/
/**
 * @file    nyLockGuard.hpp
 * @author  Dalia Castellanos
 * @date    05/03/2026
 * @brief   Defines the LockGuard class template for RAII-style mutex locking.
 * 
 * Defines a `LockGuard` class template that provides RAII-style locking of
 * mutex-like objects. The `LockGuard` locks the given mutex on construction and
 * automatically unlocks it on destruction, ensuring that locks are properly
 * released even in the presence of exceptions or early returns.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

namespace nyEngineSDK
{
  /**
   * @brief RAII helper that locks a mutex-like object on construction and
   *        unlocks it on destruction.
   * @bug No known bugs
   */
  template <class TMutex>
  class LockGuard
  {
   public:
    /**
     * @brief Locks the given mutex-like object for the lifetime of this guard.
     * @bug No known bugs
     */
    explicit LockGuard(TMutex& mutex) noexcept
      : mMutex(mutex)
    {
      mMutex.lock();
    }

    /**
     * @brief Deleted copy constructor to prevent copying of the lock guard.
     */
    LockGuard(const LockGuard&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying of the lock guard.
     */
    LockGuard&
    operator=(const LockGuard&) = delete;

    /**
     * @brief Unlocks the guarded mutex-like object.
     * @bug No known bugs
     */
    ~LockGuard() noexcept
    {
      mMutex.unlock();
    }

   private:
    /**
     * @brief Reference to the mutex-like object being guarded. This reference is
     *        initialized in the constructor and is used to lock/unlock the mutex.
     */
    TMutex& mMutex;
  };
} // namespace nyEngineSDK