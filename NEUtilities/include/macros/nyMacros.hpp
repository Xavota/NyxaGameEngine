/******************************************************************************/
/**
 * @file    nyMacros.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines common macros for the Utilities library.
 *
 * Defines common macros for the Utilities library, including inline control,
 * branch prediction hints, debug break, unreachable code, and attributes. These
 * macros are designed to improve code readability, performance, and maintainability
 * across different compilers and platforms by providing a consistent interface for
 * common patterns and compiler-specific features.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <atomic>
#include <cstdlib>
#include <utility>

#include "macros/nyConfig.hpp"
#include "macros/nyPlatform.hpp"
#include "macros/nyCompiler.hpp"
#include "macros/nyBuild.hpp"
#include "macros/nyFeatures.hpp"

// ============================
// Inline control
// ============================

#if NY_COMPILER_MSVC
  #define NY_FORCE_INLINE __forceinline
  #define NY_NO_INLINE __declspec(noinline)
#elif NY_COMPILER_CLANG || NY_COMPILER_GCC
  #define NY_FORCE_INLINE inline __attribute__((always_inline))
  #define NY_NO_INLINE __attribute__((noinline))
#else
  #define NY_FORCE_INLINE inline
  #define NY_NO_INLINE
#endif

// ============================
// Branch prediction
// ============================

#if (NY_COMPILER_CLANG || NY_COMPILER_GCC)
  #define NY_LIKELY(x) (__builtin_expect(!!(x), 1))
  #define NY_UNLIKELY(x) (__builtin_expect(!!(x), 0))
#else
  #define NY_LIKELY(x) (x)
  #define NY_UNLIKELY(x) (x)
#endif

#if NY_CPP20
  #define NY_IF_LIKELY(cond) if (cond) [[likely]]
  #define NY_IF_UNLIKELY(cond) if (cond) [[unlikely]]
#else
  #define NY_IF_LIKELY(cond) if (cond)
  #define NY_IF_UNLIKELY(cond) if (cond)
#endif

// ============================
// Debug break
// ============================

#if NY_OS_WINDOWS
  #if NY_COMPILER_MSVC
    #define NY_DEBUG_BREAK() __debugbreak()
  #elif (NY_COMPILER_CLANG || NY_COMPILER_GCC)
    #define NY_DEBUG_BREAK() __builtin_trap()
  #else
    #define NY_DEBUG_BREAK() ((void)0)
  #endif
#elif (NY_COMPILER_CLANG || NY_COMPILER_GCC)
  #define NY_DEBUG_BREAK() __builtin_trap()
#else
  #define NY_DEBUG_BREAK() ((void)0)
#endif

// ============================
// Unreachable
// ============================

#if defined(__cpp_lib_unreachable) && (__cpp_lib_unreachable >= 202202L)
  #define NY_UNREACHABLE() ::std::unreachable()
#else
  #if NY_COMPILER_MSVC
    #define NY_UNREACHABLE() __assume(0)
  #elif (NY_COMPILER_CLANG || NY_COMPILER_GCC)
    #define NY_UNREACHABLE() __builtin_unreachable()
  #else
    #define NY_UNREACHABLE() do { } while (0)
  #endif
#endif

// ============================
// Attributes
// ============================

#if NY_HAS_CPP_ATTRIBUTE(nodiscard)
  #define NY_NODISCARD [[nodiscard]]
#else
  #define NY_NODISCARD
#endif

#if NY_HAS_CPP_ATTRIBUTE(maybe_unused)
  #define NY_MAYBE_UNUSED [[maybe_unused]]
#else
  #define NY_MAYBE_UNUSED
#endif

#if NY_HAS_CPP_ATTRIBUTE(deprecated)
  #define NY_DEPRECATED(msg) [[deprecated(msg)]]
#else
  #define NY_DEPRECATED(msg)
#endif

#define NY_CACHELINE_ALIGN alignas(NY_CACHELINE_BYTES)

namespace nyEngineSDK
{
  /***
   * @brief Assertion handler callback signature.
   */
  using AssertHandlerFn =
    void(*)(const char* expr, const char* file, int line, const char* msg) noexcept;

  namespace detail
  {
    /***
     * @brief  Default assertion handler used when no custom handler is installed.
     * @param  expr  The expression that failed.
     * @param  file  The source file where the assertion failed.
     * @param  line  The line number in the source file where the assertion failed.
     * @param  msg   An optional message provided with the assertion.
     * @bug    No known bugs
     */
    inline void
    defaultAssertHandler(const char* expr, const char* file, int line,
      const char* msg) noexcept
    {
      (void)expr; (void)file; (void)line; (void)msg;

      #if NY_BUILD_DEBUG
        NY_DEBUG_BREAK();
      #else
        std::abort();
      #endif
    }

    /***
     * @brief  Returns storage for the current assertion handler.
     * @return A reference to an atomic pointer to the current assertion handler function.
     * @bug    No known bugs
     */
    inline std::atomic<AssertHandlerFn>&
    assertHandlerStorage() noexcept
    {
      static std::atomic<AssertHandlerFn> handler{ &defaultAssertHandler };
      return handler;
    }

    /***
     * @brief  Invokes the current assertion handler with the given failure context.
     * @param  expr  The expression that failed.
     * @param  file  The source file where the assertion failed
     * @param  line  The line number in the source file where the assertion failed.
     * @param  msg   An optional message provided with the assertion.
     * @bug    No known bugs
     */
    NY_NO_INLINE inline void
    assertFail(const char* expr, const char* file, int line, const char* msg) noexcept
    {
      AssertHandlerFn fn = assertHandlerStorage().load(std::memory_order_relaxed);
      if (fn)
      {
        fn(expr, file, line, msg);
      }
      else
      {
        defaultAssertHandler(expr, file, line, msg);
      }
    }
  } // namespace detail

  /***
   * @brief  Installs a custom assertion handler (typically set by Core at startup).
   * @param  fn  The assertion handler callback to install. If null, the
   *             default handler will be used.
   * @bug    No known bugs
   */
  inline void
  setAssertHandler(AssertHandlerFn fn) noexcept
  {
    detail::assertHandlerStorage().store(
      fn ? fn : &detail::defaultAssertHandler,
      std::memory_order_relaxed);
  }

  /***
   * @brief  Returns the currently installed assertion handler.
   * @return The currently installed assertion handler callback.
   * @bug    No known bugs
   */
  inline AssertHandlerFn
  getAssertHandler() noexcept
  {
    return detail::assertHandlerStorage().load(std::memory_order_relaxed);
  }

} // namespace nyEngineSDK

#if NY_ENABLE_ASSERTS
  #define NY_ASSERT(expr) \
    do \
    { \
      if (NY_UNLIKELY(!(expr))) \
      { \
        ::nyEngineSDK::detail::assertFail(#expr, __FILE__, __LINE__, ""); \
      } \
    } while (0)

  #define NY_ASSERT_MSG(expr, msg) \
    do \
    { \
      if (NY_UNLIKELY(!(expr))) \
      { \
        ::nyEngineSDK::detail::assertFail(#expr, __FILE__, __LINE__, (msg)); \
      } \
    } while (0)
#else
  #define NY_ASSERT(expr) ((void)0)
  #define NY_ASSERT_MSG(expr, msg) ((void)0)
#endif

#define NY_PANIC(msg) \
  do \
  { \
    ::nyEngineSDK::detail::assertFail("PANIC", __FILE__, __LINE__, (msg)); \
    NY_UNREACHABLE(); \
  } while (0)

#define NY_STATIC_ASSERT(expr, msg) static_assert((expr), msg)
