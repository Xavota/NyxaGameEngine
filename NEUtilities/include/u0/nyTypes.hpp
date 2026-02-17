/*****************************************************************************/
/**
 * @file    nyTypes.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines common type aliases for the Utilities library.
 *
 * Defines common type aliases for fixed-width integers, floating-point types,
 * and size types.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "u0/nyMacros.hpp"
#include <cstdint>
#include <cstddef>

namespace nyEngineSDK
{
  using i8 = std::int8_t;
  using i16 = std::int16_t;
  using i32 = std::int32_t;
  using i64 = std::int64_t;

  using u8 = std::uint8_t;
  using u16 = std::uint16_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  using f32 = float;
  using f64 = double;

  using usize = std::size_t;
  using isize = std::ptrdiff_t;

  NY_STATIC_ASSERT(sizeof(u8) == 1, "u8 must be 1 byte");
  NY_STATIC_ASSERT(sizeof(u16) == 2, "u16 must be 2 bytes");
  NY_STATIC_ASSERT(sizeof(u32) == 4, "u32 must be 4 bytes");
  NY_STATIC_ASSERT(sizeof(u64) == 8, "u64 must be 8 bytes");

  NY_STATIC_ASSERT(sizeof(i8) == 1, "i8 must be 1 byte");
  NY_STATIC_ASSERT(sizeof(i16) == 2, "i16 must be 2 bytes");
  NY_STATIC_ASSERT(sizeof(i32) == 4, "i32 must be 4 bytes");
  NY_STATIC_ASSERT(sizeof(i64) == 8, "i64 must be 8 bytes");

  NY_STATIC_ASSERT(sizeof(f32) == 4, "f32 must be 4 bytes");
  NY_STATIC_ASSERT(sizeof(f64) == 8, "f64 must be 8 bytes");
} // namespace nyEngineSDK