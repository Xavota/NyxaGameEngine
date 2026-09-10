/******************************************************************************/
/**
 * @file    nyThread.hpp
 * @author  Dalia Castellanos
 * @date    05/03/2026
 * @brief   Defines the Thread class for managing threads of execution.
 *
 * Defines a simple `Thread` class that provides basic thread management
 * functionality by wrapping `std::thread`.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <thread>
#include <utility>

#include "macros/nyBuild.hpp"
#include "macros/nyMacros.hpp"

namespace nyEngineSDK
{
  /**
   * @brief Thin wrapper over std::thread for engine-wide consistency.
   * @bug No known bugs
   */
  class Thread
  {
  public:
    /**
     * @brief Constructs an empty thread object (not joinable).
     * @bug No known bugs
     */
    Thread() noexcept = default;

    /**
     * @brief Deleted copy constructor to prevent copying of the thread object.
     */
    Thread(const Thread&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying of the thread object.
     */
    Thread&
    operator=(const Thread&) = delete;

    /**
     * @brief Moves a thread object, transferring ownership.
     * @bug No known bugs
     */
    Thread(Thread&& other) noexcept
      : mThread(std::move(other.mThread))
    {
    }

    /**
     * @brief Move-assigns a thread object, transferring ownership.
     * @bug No known bugs
     */
    Thread&
    operator=(Thread&& other) noexcept
    {
      if (this == &other)
      {
        return *this;
      }

      if (mThread.joinable())
      {
        mThread.join();
      }

      mThread = std::move(other.mThread);
      return *this;
    }

    /**
     * @brief Joins the thread if joinable.
     * @bug No known bugs
     */
    ~Thread() noexcept
    {
      #if NY_BUILD_DEBUG
        NY_ASSERT_MSG(
          !mThread.joinable() || mThread.get_id() == std::this_thread::get_id(),
          "Thread was still joinable at destruction. Ensure it is joined or"
          " detached before destruction."
        );
      #else
        if (mThread.joinable() && mThread.get_id() != std::this_thread::get_id())
        {
          mThread.join();
        }
      #endif
    }

    /**
     * @brief Starts the thread with the given callable and arguments.
     * @bug No known bugs
     */
    template <class Fn, class... Args>
    void
    start(Fn&& fn, Args&&... args)
    {
      if (mThread.joinable())
      {
        mThread.join();
      }

      mThread = std::thread(std::forward<Fn>(fn), std::forward<Args>(args)...);
    }

    /**
     * @brief Returns whether this thread object represents a joinable thread.
     * @bug No known bugs
     */
    bool
    isJoinable() const noexcept
    {
      return mThread.joinable();
    }

    /**
     * @brief Blocks until the thread finishes execution.
     * @bug No known bugs
     */
    void
    join() noexcept
    {
      if (mThread.joinable())
      {
        mThread.join();
      }
    }

    /**
     * @brief Detaches the thread, allowing it to run independently.
     * @bug No known bugs
     */
    void
    detach() noexcept
    {
      if (mThread.joinable())
      {
        mThread.detach();
      }
    }

    /**
     * @brief Returns the native thread handle.
     * @bug No known bugs
     */
    std::thread::native_handle_type
    nativeHandle() noexcept
    {
      return mThread.native_handle();
    }

  private:
    /**
     * @brief The underlying std::thread object that manages the thread of execution.
     */
    std::thread mThread;
  };
} // namespace nyEngineSDK