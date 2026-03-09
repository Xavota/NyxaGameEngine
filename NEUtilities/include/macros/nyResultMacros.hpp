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
#define U0_OK() ::u0::Result<void>(::u0::Status::ok())

// Create a Status error quickly (non-formatted)
#define U0_ERR(level, module, messageSv) \
  ::u0::Status::error((level), (module), (messageSv))

// Create a formatted Status error quickly
#define U0_ERRF(level, module, fmt, ...) \
  ::u0::Status::errorf((level), (module), (fmt), ##__VA_ARGS__)

// Propagate an error Result<void> upward if it failed
#define U0_TRY(expr) \
  do \
  { \
    auto _u0_try_result = (expr); \
    if (!_u0_try_result) \
    { \
      return _u0_try_result.error(); \
    } \
  } while (0)

// Propagate an error Result<T> upward if it failed
// and on success assign the extracted value to outVar (moved).
#define U0_TRY_ASSIGN(outVar, expr) \
  do \
  { \
    auto _u0_try_result = (expr); \
    if (!_u0_try_result) \
    { \
      return _u0_try_result.error(); \
    } \
    (outVar) = std::move(_u0_try_result.value()); \
  } while (0)