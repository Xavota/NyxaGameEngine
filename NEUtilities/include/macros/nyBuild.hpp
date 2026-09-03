/******************************************************************************/
/**
 * @file    nyBuild.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines build configuration macros for the Utilities library.
 *
 * Defines macros for build configuration such as debug/release mode and
 * sanitizer detection.These macros can be used throughout the library to
 * conditionally compile code based on the build configuration.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include "macros/nyFeatures.hpp"

// Debug detection
#if defined(NDEBUG)
  #define NY_BUILD_DEBUG 0
  #define NY_BUILD_RELEASE 1
#else
  #define NY_BUILD_DEBUG 1
  #define NY_BUILD_RELEASE 0
#endif

// Sanitizers (best-effort)
#if NY_HAS_FEATURE(address_sanitizer)
  #define NY_SANITIZER_ASAN 1
#else
  #define NY_SANITIZER_ASAN 0
#endif
  #if NY_HAS_FEATURE(thread_sanitizer)
  #define NY_SANITIZER_TSAN 1
#else
  #define NY_SANITIZER_TSAN 0
#endif
#if NY_HAS_FEATURE(memory_sanitizer)
  #define NY_SANITIZER_MSAN 1
#else
  #define NY_SANITIZER_MSAN 0
#endif
