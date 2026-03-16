/*****************************************************************************/
/**
 * @file    nyResultMacros.hpp
 * @author  Dalia Castellanos
 * @date    19/02/2026
 * @brief   Defines convenient macros for working with Result and Status types.
 * 
 * Defines convenient macros for working with `Result` and `Status` types,
 * including helpers for creating success and error results, as well as macros
 * for propagating errors upward in the call stack.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "types/nyResult.hpp"

// Result<void> success helper
#define NY_OK() ::nyEngineSDK::Result<void>(::nyEngineSDK::Status::ok())

// Create a Status error quickly (non-formatted)
#define NY_ERR(level, module, messageSv) \
  ::nyEngineSDK::Status::error((level), (module), (messageSv))

// Create a formatted Status error quickly
#define NY_ERRF(level, module, fmt, ...) \
  ::nyEngineSDK::Status::errorf((level), (module), (fmt), ##__VA_ARGS__)

// Propagate an error Result<void> upward if it failed
#define NY_TRY(expr) \
  do \
  { \
    auto _ny_try_result = (expr); \
    if (!_ny_try_result) \
    { \
      return _ny_try_result.error(); \
    } \
  } while (0)

// Propagate an error Result<T> upward if it failed
// and on success assign the extracted value to outVar (moved).
#define NY_TRY_ASSIGN(outVar, expr) \
  do \
  { \
    auto _ny_try_result = (expr); \
    if (!_ny_try_result) \
    { \
      return _ny_try_result.error(); \
    } \
    (outVar) = std::move(_ny_try_result.value()); \
  } while (0)