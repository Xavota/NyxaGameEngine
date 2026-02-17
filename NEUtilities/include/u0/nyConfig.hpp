/*****************************************************************************/
/**
 * @file    nyConfig.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines global configuration macros for the Utilities library.
 *
 * Defines global configuration macros for the Utilities library, such as enabling
 * assertions, exceptions, RTTI, and setting the cache line size. These macros
 * can be overridden by defining them before including this header, allowing users
 * to customize the behavior of the library to their needs. This file is intended
 * to be the only file users need to edit for global defaults, while other
 * configuration should be auto-detected or set in more specific headers.
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once

// Layer 0 config for Utilities.
// This is intended to be the only file you edit for global defaults.
// Everything else should be auto-detected.

// 0 = off, 1 = on
#ifndef NY_ENABLE_ASSERTS
  #define NY_ENABLE_ASSERTS 1
#endif

#ifndef NY_ENABLE_EXCEPTIONS
  // If you disable exceptions, you should also compile with the right flags:
  // MSVC: /EHsc (on) or /EHs-c- (off), Clang/GCC: -fexceptions (on) / -fno-exceptions (off)
  #define NY_ENABLE_EXCEPTIONS 0
#endif

#ifndef NY_ENABLE_RTTI
  // MSVC: /GR (on) /GR- (off), Clang/GCC: -frtti (on) / -fno-rtti (off)
  #define NY_ENABLE_RTTI 0
#endif

#ifndef NY_CACHELINE_BYTES
  // Common values: 64 on most desktop CPUs, sometimes 128. Keep 64 unless you truly know otherwise.
  #define NY_CACHELINE_BYTES 64
#endif

#ifndef NY_FORCE_UTF8_INTERNAL
  // Recommended: keep UTF-8 as internal string encoding.
  #define NY_FORCE_UTF8_INTERNAL 1
#endif
