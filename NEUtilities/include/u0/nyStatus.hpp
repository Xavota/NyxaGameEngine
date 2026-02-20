/*****************************************************************************/
/**
 * @file    nyStatus.hpp
 * @author  Dalia Castellanos
 * @date    18/02/2026
 * @brief   Defines a simple status class for representing success or error
 *          results.
 * 
 * Defines a simple `Status` class that represents the result of an operation,
 * which can be either success or error. The `Status` class provides static
 * factory methods to create success and error statuses, as well as member
 * functions to query the status and retrieve associated information such as
 * log level, module, and message.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "u0/nyTypes.hpp"
#include "u0/nyStringView.hpp"
#include "u0/nyFormat.hpp"
#include "u0/nyLog.hpp"

#include <cstdint>

#ifndef NY_STATUS_MESSAGE_CAP
#define NY_STATUS_MESSAGE_CAP 1024
#endif

namespace nyEngineSDK
{
  /*
   * @brief  Represents the result of an operation, which can be either success
   *         or error.
   * @bug    No known bugs.
   */
  class Status
  {
  public:
    static constexpr u16 MessageCap = static_cast<u16>(NY_STATUS_MESSAGE_CAP);

    /*
     * @brief  Creates a successful status with no message.
     * @return A Status object representing success with no message.
     * @bug    No known bugs.
     */
    static Status ok() noexcept
    {
      return Status();
    }

    /*
     * @brief  Creates an error status with the specified log level, module,
     *         and message.
     * @param  level    The log level associated with the error status. This can
     *                  be used to indicate the severity of the error
     *                  (e.g., Warning, Error, Fatal).
     * @param  module   The module or component associated with the error status.
     *                  This can be used to indicate which part of the system the
     *                  error originated from.
     * @param  message  The error message describing the error. This should
     *                  provide details about the error condition and can be
     *                  used for debugging or logging purposes.
     * @return A Status object representing the error with the specified log
     *         level, module, and message.
     * @bug    No known bugs.
     */
    static Status
    error(LogLevel level, StringView module, StringView message) noexcept
    {
      Status s;
      s.mOk = false;
      s.mLevel = level;
      s.mModule = module;
      s.setMessage(message);
      return s;
    }

    /*
     * @brief  Creates an error status with the specified log level, module, and
     *         formatted message.
     * @param  level   The log level associated with the error status. This can
     *                 be used to indicate the severity of the error
     *                 (e.g., Warning, Error, Fatal).
     * @param  module  The module or component associated with the error status.
     *                 This can be used to indicate which part of the system the
     *                 error originated from.
     * @param  fmt     The format string for the error message, using `{}` as
     *                 placeholders for arguments.
     * @param  args    The arguments to replace the `{}` placeholders in the
     *                 format string. Supported types include StringView,
     *                 C-strings, characters, integral types, floating-point
     *                 types, and booleans.
     * @return A Status object representing the error with the specified log
     *         level, module, and formatted message.
     * @bug    No known bugs.
     */
    template <class... Args>
    static Status
    errorf(LogLevel level, StringView module, StringView fmt,
      const Args&... args) noexcept
    {
      Status s;
      s.mOk = false;
      s.mLevel = level;
      s.mModule = module;

      StringView out = format_to(s.mMessage, static_cast<usize>(MessageCap),
        fmt, args...);

      s.mMessageLen = static_cast<u16>(out.size());
      return s;
    }

    /*
     * @brief  Returns true if the status represents success, false if it
     *         represents an error.
     * @return True if the status is successful, false if it is an error.
     * @bug    No known bugs.
     */
    bool
    isOk() const noexcept
    {
      return mOk;
    }

    /*
     * @brief  Returns true if the status represents an error, false if it
     *         represents success.
     * @return True if the status is an error, false if it is successful.
     * @bug    No known bugs.
     */
    bool
    isError() const noexcept
    {
      return !mOk;
    }

    /*
     * @brief  Returns the log level associated with the status. For error
     *         statuses, this indicates the severity of the error
     *         (e.g., Warning, Error, Fatal). For successful statuses, this
     *         will typically be LogLevel::Info.
     * @return The log level associated with the status.
     * @bug    No known bugs.
     */
    LogLevel
    level() const noexcept
    {
      return mLevel;
    }

    /*
     * @brief  Returns the module or component associated with the status.
     *         This can be used to indicate which part of the system the status
     *         originated from.
     * @return The module associated with the status.
     * @bug    No known bugs.
     */
    StringView
    module() const noexcept
    {
      return mModule;
    }

    /*
     * @brief  Returns the message associated with the status. For error
     *         statuses, this will contain details about the error condition.
     *         For successful statuses, this may be empty or contain
     *         informational messages.
     * @return The message associated with the status.
     * @bug    No known bugs.
     */
    StringView
    message() const noexcept
    {
      return StringView(mMessage, static_cast<usize>(mMessageLen));
    }

  private:
    /*
     * @brief  Private constructor for creating a successful status with no
     *         message.
     * @return A Status object representing success with no message.
     * @bug    No known bugs.
     */
    Status() noexcept :
      mOk(true), mLevel(LogLevel::Info), mModule(), mMessage{ '\0' },
      mMessageLen(0) {}

    /*
     * @brief  Helper function to set the message for the status, ensuring it
     *         fits within the fixed-size message buffer and properly null-terminated.
     * @param  msg  The message to set for the status. If the message exceeds the
     *              capacity of the message buffer, it will be truncated to fit.
     * @bug    No known bugs.
     */
    void
    setMessage(StringView msg) noexcept
    {
      StringView out = format_to(mMessage, static_cast<usize>(MessageCap),
        "{}", msg);

      mMessageLen = static_cast<u16>(out.size());
    }

  private:
    /*
     * @brief  Indicates whether the status represents success (true) or error
     *        (false).
     */
    bool mOk;
    /*
     * @brief  The log level associated with the status. For error statuses,
     *         this indicates the severity of the error (e.g., Warning, Error,
     *         Fatal). For successful statuses, this will typically be
     *         LogLevel::Info.
     */
    LogLevel mLevel;
    /*
     * @brief  The module or component associated with the status. This can be
     *         used to indicate which part of the system the status originated from.
     */
    StringView mModule;
    /*
     * @brief  The message associated with the status. For error statuses, this
     *         will contain details about the error condition. For successful
     *         statuses, this may be empty or contain informational messages.
     *         This is stored in a fixed-size character array with a capacity
     *         defined by MessageCap.
     */
    char mMessage[MessageCap];
    /*
     * @brief  The length of the message stored in mMessage.
     */
    u16 mMessageLen;
  };
} // namespace nyEngineSDK