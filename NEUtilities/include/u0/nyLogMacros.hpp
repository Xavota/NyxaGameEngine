/*****************************************************************************/
/**
 * @file    nyLogMacros.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines logging macros for the Utilities library.
 *
 * Defines convenient logging macros for different log levels (Trace, Info,
 * Warning, Error, Fatal) that automatically include the engine name and module
 * name. The Trace macro is conditionally compiled out in release builds for
 * performance reasons, while the other macros are always available but still
 * filtered at runtime based on the current log level. These macros provide a
 * simple and consistent way to emit log messages throughout the engine code, with
 * the flexibility to customize the log sink and log level as needed.
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once

#include "nyLog.hpp"

// Engine name lives here for now. You can move this into Core later if you prefer.
namespace nyEngineSDK
{
  inline constexpr StringView ENGINE_NAME = "Nyxa Engine";
}

// Hybrid compile-time rule:
// Release: strip Trace completely
// Debug: keep Trace (still runtime-filtered)
#if NY_BUILD_RELEASE
  #define NY_LOG_TRACE(module, fmt, ...) ((void)0)
#else
  #define NY_LOG_TRACE(module, fmt, ...) \
    ::nyEngineSDK::logf(::nyEngineSDK::LogLevel::Trace, ::nyEngineSDK::ENGINE_NAME, (module), (fmt), ##__VA_ARGS__)
#endif

#define NY_LOG_INFO(module, fmt, ...) \
  ::nyEngineSDK::logf(::nyEngineSDK::LogLevel::Info, ::nyEngineSDK::ENGINE_NAME, (module), (fmt), ##__VA_ARGS__)

#define NY_LOG_WARN(module, fmt, ...) \
  ::nyEngineSDK::logf(::nyEngineSDK::LogLevel::Warning, ::nyEngineSDK::ENGINE_NAME, (module), (fmt), ##__VA_ARGS__)

#define NY_LOG_ERROR(module, fmt, ...) \
  ::nyEngineSDK::logf(::nyEngineSDK::LogLevel::Error, ::nyEngineSDK::ENGINE_NAME, (module), (fmt), ##__VA_ARGS__)

#define NY_LOG_FATAL(module, fmt, ...) \
  ::nyEngineSDK::logf(::nyEngineSDK::LogLevel::Fatal, ::nyEngineSDK::ENGINE_NAME, (module), (fmt), ##__VA_ARGS__)
