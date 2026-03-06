/******************************************************************************/
/**
 * @file    nyLog.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines the public logging API for the Utilities library.
 *
 * Defines the public logging API for the Utilities library, including log
 * levels, log sink callback, and functions to set/get the log sink and log
 * level. The log sink callback can be used to route log messages to different
 * outputs, such as console, file, or platform-specific logging systems.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include "nyApi.hpp"
#include "u0/nyTypes.hpp"
#include "u0/nyStringView.hpp"

namespace nyEngineSDK
{
  enum class LogLevel : u8 {
    Trace = 0, Info, Warning, Error, Fatal
  };

  /**
   * @brief  Default log sink used when no custom sink is installed. It handles
   *         fatal logs by breaking in debug builds or aborting in release builds.
   */
  using LogSinkFn = void(*)(LogLevel,
    StringView engine,
    StringView module,
    StringView text) noexcept;

  /**
   * @brief  Installs a custom log sink callback (typically set by Core at startup).
   * @param  fn  The log sink callback to install. If null, the default sink will be used.
   * @bug    No known bugs
   */
  NY_API void set_log_sink(LogSinkFn fn) noexcept;
  /**
   * @brief  Returns the currently installed log sink callback.
   * @bug    No known bugs
   */
  NY_API LogSinkFn get_log_sink() noexcept;

  /**
   * @brief  Sets the current log level. Messages below this level will be
   *         filtered out.
   * @param  lvl  The log level to set. Messages below this level will be filtered out.
   * @bug    No known bugs
   */
  NY_API void set_log_level(LogLevel lvl) noexcept;
  /**
   * @brief  Returns the current log level.
   * @bug    No known bugs
   */
  NY_API LogLevel get_log_level() noexcept;

  /**
   * @brief  Returns true if a message at the given log level would be emitted
   *         based on the current log level setting, false if it would be
   *         filtered out.
   * @param  lvl  The log level to check. Returns true if messages at this level
   *              would be emitted, false if they would be filtered out.
   * @bug    No known bugs
   */
  NY_API bool log_enabled(LogLevel lvl) noexcept;

  /**
   * @brief  Low-level logging function that emits a log message with the given
   *         log level, engine name, module name, and already formatted text.
   * @param  lvl     The log level of the message.
   * @param  engine  The name of the engine (e.g. "Nyxa Engine").
   * @param  module  The name of the module emitting the log (e.g. "Core", "Renderer").
   * @param  text    The already formatted log message text to emit.
   * @bug    No known bugs
   */
  NY_API void log_text(LogLevel lvl, StringView engine, StringView module, StringView text) noexcept;
} // namespace nyEngineSDK