/******************************************************************************/
/**
 * @file    nyFormat.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines a simple string formatting function for the Utilities library.
 *
 * Defines a simple string formatting function `nyEngineSDK::format` that
 * supports basic placeholder replacement using `{}` syntax. It supports
 * formatting of strings, characters, integral types, floating-point types,
 * and booleans.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <type_traits>
#include <charconv>
#include <cstring>
#include <cstdio>

#include "types/nyTypes.hpp"
#include "types/nyStringView.hpp"
#include "macros/nyMacros.hpp"

namespace nyEngineSDK
{
  namespace detail
  {
    /**
     * @brief  Helper function to calculate the length of a null-terminated C-string.
     * @param  s  Pointer to a null-terminated C-string. If null, the length is considered 0.
     * @return Length of the C-string, not including the null terminator. If the
     *         pointer is null, returns 0.
     * @bug    No known bugs.
     */
    inline usize
    cstr_len(const char* s) noexcept {
      return s ? static_cast<usize>(std::strlen(s)) : 0;
    }

    /**
     * @brief  Helper function to copy bytes from a source to a destination buffer,
     *         respecting the capacity and current position, and ensuring null
     *         termination if possible.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  src   Pointer to the source bytes to copy. If null, no copying occurs.
     * @param  len   Number of bytes to copy from the source. If zero, no copying occurs.
     * @return Updated position in the destination buffer after copying.
     *         This will not exceed cap - 1 to ensure space for a null
     *         terminator if possible.
     * @bug    No known bugs.
     */
    inline usize
    copy_bytes(char* dst, usize cap, usize pos, const char* src, usize len) noexcept {
      if (!dst || cap == 0) return pos;
      if (!src || len == 0) return pos;

      // Reserve 1 byte for null terminator if possible
      usize max_write = (cap > 0) ? (cap - 1) : 0;
      if (pos >= max_write) return pos;

      usize to_write = len;
      if (pos + to_write > max_write) to_write = max_write - pos;

      if (to_write > 0) {
        std::memcpy(dst + pos, src, to_write);
        pos += to_write;
      }
      return pos;
    }

    /**
     * @brief  Helper function to append a null-terminated C-string to a destination
     *         buffer, respecting the capacity and current position, and ensuring
     *         null termination if possible.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  s     Pointer to the null-terminated C-string to append. If null,
     *               it is treated as an empty string and no copying occurs.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_cstr(char* dst, usize cap, usize pos, const char* s) noexcept {
      return copy_bytes(dst, cap, pos, s, cstr_len(s));
    }

    /**
     * @brief  Helper function to append a StringView to a destination buffer,
     *         respecting the capacity and current position, and ensuring null
     *         termination if possible.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  sv    The StringView to append. If empty, no copying occurs.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_sv(char* dst, usize cap, usize pos, StringView sv) noexcept {
      return copy_bytes(dst, cap, pos, sv.data(), sv.size());
    }

    /**
     * @brief  Helper function to append a single character to a destination
     *         buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  c     The character to append.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_char(char* dst, usize cap, usize pos, char c) noexcept {
      if (!dst || cap == 0) return pos;
      usize max_write = cap - 1;
      if (pos >= max_write) return pos;
      dst[pos++] = c;
      return pos;
    }

    /**
     * @brief  Helper function to append an integral value to a destination buffer,
     *         respecting the capacity and current position, and ensuring null
     *         termination if possible.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The integral value to append.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    template <class T>
    inline usize
    append_integral(char* dst, usize cap, usize pos, T v) noexcept {
      // Enough for 64-bit + sign
      char buf[32];
      auto res = std::to_chars(buf, buf + sizeof(buf), v);
      if (res.ec != std::errc{}) return pos;
      return copy_bytes(dst, cap, pos, buf, static_cast<usize>(res.ptr - buf));
    }

    /**
     * @brief  Helper function to append a floating point value to a destination
     *         buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The floating point value to append.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_float(char* dst, usize cap, usize pos, double v) noexcept {
      // Simple, portable float formatting (no allocations)
      // You can tune precision later.
      char buf[64];
      int n = std::snprintf(buf, sizeof(buf), "%.6f", v);
      if (n <= 0) return pos;
      return copy_bytes(dst, cap, pos, buf, static_cast<usize>(n));
    }

    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    // Append one argument (overload set)
    inline usize
    append_one(char* dst, usize cap, usize pos, StringView v) noexcept
    {
      return append_sv(dst, cap, pos, v);
    }
    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_one(char* dst, usize cap, usize pos, const char* v) noexcept
    {
      return append_cstr(dst, cap, pos, v);
    }
    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_one(char* dst, usize cap, usize pos, char* v) noexcept
    {
      return append_cstr(dst, cap, pos, v);
    }
    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_one(char* dst, usize cap, usize pos, char v) noexcept
    {
      return append_char(dst, cap, pos, v);
    }
    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_one(char* dst, usize cap, usize pos, bool v) noexcept
    {
      return append_cstr(dst, cap, pos, v ? "true" : "false");
    }

    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_one(char* dst, usize cap, usize pos, float v) noexcept
    {
      return append_float(dst, cap, pos, static_cast<double>(v));
    }
    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    inline usize
    append_one(char* dst, usize cap, usize pos, double v) noexcept
    {
      return append_float(dst, cap, pos, v);
    }

    /**
     * @brief  Helper function to append a single argument of various supported types
     *         to a destination buffer, respecting the capacity and current position, and
     *         ensuring null termination if possible. This is an overload set that
     *         supports StringView, C-strings, characters, integral types, floating-point
     *         types, and booleans.
     * @param  dst   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  v     The value to append. Supported types include StringView, C-strings,
     *               characters, integral types, floating-point types, and booleans.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    template <class T,
      class = std::enable_if_t<std::is_integral<T>::value
                            && !std::is_same<T, bool>::value>>
    inline usize
    append_one(char* dst, usize cap, usize pos, T v) noexcept
    {
      if constexpr (std::is_signed<T>::value) return append_integral(
        dst, cap, pos, static_cast<long long>(v));
      else return append_integral(dst, cap, pos, static_cast<unsigned long long>(v));
    }

    /**
     * @brief  Base case for the recursive format implementation. When there are
     *         no more arguments to replace, this function simply copies the
     *         remaining format string to the output buffer, respecting capacity
     *         and ensuring null termination if possible.
     * @param  out   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  fmt   The remaining format string to copy. This is treated as a
     *               literal string with no placeholders since there are no more
     *               arguments.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    // Base case: no more args, copy rest of format literally
    inline usize
    format_impl(char* out, usize cap, usize pos, StringView fmt) noexcept
    {
      return copy_bytes(out, cap, pos, fmt.data(), fmt.size());
    }

    /**
     * @brief  Recursive implementation of the format function. This function
     *         processes the format string, replacing the first occurrence of
     *         `{}` with the string representation of the first argument, and
     *         then recurses on the remainder of the format string and the
     *         remaining arguments. It respects the capacity of the output
     *         buffer and ensures null termination if possible.
     * @param  out   Pointer to the destination buffer where bytes will be
     *               copied. If null, no copying occurs.
     * @param  cap   Total capacity of the destination buffer in bytes.
     *               If zero, no copying occurs.
     * @param  pos   Current position in the destination buffer where copying
     *               should start. This is updated and returned after copying.
     * @param  fmt   The format string to process. The first occurrence of `{}`
     *               will be replaced with the string representation of the
     *               first argument.
     * @param  a0    The first argument to replace the first `{}` placeholder in
     *               the format string. Supported types include StringView,
     *               C-strings, characters, integral types, floating-point types,
     *               and booleans.
     * @param  rest  The remaining arguments to replace subsequent `{}`
     *               placeholders in the format string. This is passed
     *               recursively until all arguments are processed.
     * @return Updated position in the destination buffer after copying.
     * @bug    No known bugs.
     */
    // Recursive: replace first {} with one arg
    template <class Arg0, class... Args>
    inline usize
    format_impl(char* out, usize cap, usize pos, StringView fmt,
      const Arg0& a0, const Args&... rest) noexcept {
      const char* s = fmt.data();
      usize n = fmt.size();

      for (usize i = 0; i + 1 < n; ++i) {
        if (s[i] == '{' && s[i + 1] == '}') {
          // Copy prefix before {}
          pos = copy_bytes(out, cap, pos, s, i);
          // Append arg
          pos = append_one(out, cap, pos, a0);
          // Recurse on remainder after {}
          StringView tail(s + i + 2, n - (i + 2));
          return format_impl(out, cap, pos, tail, rest...);
        }
      }

      // No placeholder found, copy all and ignore extra args
      return copy_bytes(out, cap, pos, s, n);
    }

  } // namespace detail

  /**
   * @brief  Formats a string by replacing `{}` placeholders in the format
   *         string with the string representations of the provided arguments.
   * @param  out   Pointer to the destination buffer where bytes will be
   *               copied. If null, no copying occurs.
   * @param  cap   Total capacity of the destination buffer in bytes.
   *               If zero, no copying occurs.
   * @param  pos   Current position in the destination buffer where copying
   *               should start. This is updated and returned after copying.
   * @param  fmt   The format string to process. The first occurrence of `{}`
   *               will be replaced with the string representation of the
   *               first argument.
   * @param  args   The arguments to replace `{}` placeholders in the format
   *                string. Supported types include StringView, C-strings,
   *                characters, integral types, floating-point types, and booleans.
   * @return A StringView representing the formatted string that was written to
   *         the output buffer. The size of the StringView will be the number
   *         of characters written, not including the null terminator. If the
   *         output buffer was too small to hold the entire formatted string,
   *         the returned StringView will contain the truncated string that fits
   *         in the buffer, and will still be null-terminated if the buffer has
   *         at least 1 byte of capacity.
   * @bug    No known bugs.
   */
  template <class... Args>
  inline StringView
  format_to(char* out, usize cap, StringView fmt, const Args&... args) noexcept {
    if (!out || cap == 0) return StringView{};
    usize pos = 0;
    pos = detail::format_impl(out, cap, pos, fmt, args...);
    // Null terminate if possible
    out[(pos < cap) ? pos : (cap - 1)] = '\0';
    return StringView(out, (pos < cap) ? pos : (cap - 1));
  }
} // namespace nyEngineSDK