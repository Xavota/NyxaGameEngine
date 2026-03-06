/******************************************************************************/
/**
 * @file    nyConditionVariable.hpp
 * @author  Dalia Castellanos
 * @date    05/03/2026
 * @brief   Defines the ConditionVariable class for thread synchronization.
 * 
 * Defines a simple `ConditionVariable` class that provides basic thread
 * synchronization functionality by wrapping `std::condition_variable`. The
 * `ConditionVariable` class provides methods to notify one or all waiting
 * threads, as well as to wait for a notification while holding a mutex.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <condition_variable>

#include "u0/nyMutex.hpp"

namespace nyEngineSDK
{
  /**
   * @brief Thin wrapper over std::condition_variable.
   * @bug No known bugs
   */
  class ConditionVariable
  {
   public:
    /**
     * @brief Wakes one waiting thread.
     * @bug No known bugs
     */
    void
    notifyOne() noexcept
    {
      mCV.notify_one();
    }

    /**
     * @brief Wakes all waiting threads.
     * @bug No known bugs
     */
    void
    notifyAll() noexcept
    {
      mCV.notify_all();
    }

    /**
     * @brief Waits until notified.
     * @bug No known bugs
     */
    void
    wait(Mutex& mutex)
    {
      std::unique_lock<std::mutex> lock(mutex.mMutex);
      mCV.wait(lock);
    }

    /**
     * @brief Waits until notified or predicate becomes true.
     * @bug No known bugs
     */
    template <class Predicate>
    void
    wait(Mutex& mutex, Predicate pred)
    {
      std::unique_lock<std::mutex> lock(mutex.mMutex);
      mCV.wait(lock, pred);
    }

   private:
    /**
     * @brief The underlying std::condition_variable object that manages the
     *        waiting and notification of threads.
     */
    std::condition_variable mCV;
  };
} // namespace nyEngineSDK