/*****************************************************************************/
/**
 * @file    nyPlatform.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines platform and architecture detection macros for the Utilities library.
 *
 * Defines macros to detect the target operating system, architecture, and
 * endianness for the Utilities library. These macros can be used throughout the
 * library to conditionally compile code based on the target platform, allowing
 * for better portability and optimization across different operating systems and
 * architectures.
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once

// OS detection
#if defined(_WIN32) || defined(_WIN64)
  #define NY_OS_WINDOWS 1
#else
  #define NY_OS_WINDOWS 0
#endif

#if defined(__APPLE__) && defined(__MACH__)
  #define NY_OS_APPLE 1
#else
  #define NY_OS_APPLE 0
#endif

#if defined(__linux__)
  #define NY_OS_LINUX 1
#else
  #define NY_OS_LINUX 0
#endif

#if defined(__ANDROID__)
  #define NY_OS_ANDROID 1
#else
  #define NY_OS_ANDROID 0
#endif

#if defined(__EMSCRIPTEN__)
  #define NY_OS_EMSCRIPTEN 1
#else
  #define NY_OS_EMSCRIPTEN 0
#endif

// Convenience group
#define NY_OS_POSIX (NY_OS_LINUX || NY_OS_APPLE || NY_OS_ANDROID)

// Architecture detection
#if defined(_M_X64) || defined(__x86_64__)
  #define NY_ARCH_X86_64 1
#else
  #define NY_ARCH_X86_64 0
#endif

#if defined(_M_IX86) || defined(__i386__)
  #define NY_ARCH_X86_32 1
#else
  #define NY_ARCH_X86_32 0
#endif

#if defined(_M_ARM64) || defined(__aarch64__)
  #define NY_ARCH_ARM64 1
#else
  #define NY_ARCH_ARM64 0
#endif

#if defined(_M_ARM) || defined(__arm__)
  #define NY_ARCH_ARM32 1
#else
  #define NY_ARCH_ARM32 0
#endif

#define NY_ARCH_X86 (NY_ARCH_X86_32 || NY_ARCH_X86_64)
#define NY_ARCH_ARM (NY_ARCH_ARM32 || NY_ARCH_ARM64)

#if defined(_M_IA64) || defined(__ia64__)
  #define NY_ARCH_IA64 1
#else
  #define NY_ARCH_IA64 0
#endif

#if (NY_ARCH_X86_64 || NY_ARCH_ARM64 || NY_ARCH_IA64)
  #define NY_64BIT 1
#else
  #define NY_64BIT 0
#endif

// Endianness detection
// Prefer standard macros if present (C++20 has <bit> with std::endian, but we keep this macro-only).
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
  #if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    #define NY_ENDIAN_LITTLE 1
    #define NY_ENDIAN_BIG 0
  #elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define NY_ENDIAN_LITTLE 0
    #define NY_ENDIAN_BIG 1
  #else
    #error "Unknown __BYTE_ORDER__"
  #endif
#elif NY_OS_WINDOWS
  // Windows targets are little-endian for the mainstream architectures you care about.
  #define NY_ENDIAN_LITTLE 1
  #define NY_ENDIAN_BIG 0
#else
  // Fallback assumption: almost all modern targets you’ll ship are little-endian.
  // If you need true big-endian support later, replace this with a compile-time probe or toolchain defines.
  #define NY_ENDIAN_LITTLE 1
  #define NY_ENDIAN_BIG 0
#endif
