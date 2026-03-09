/******************************************************************************/
/**
 * @file    nyHandle.hpp
 * @author  Dalia Castellanos
 * @date    24/02/2026
 * @brief   Defines a simple handle structure for resource management.
 * 
 * Defines a simple `Handle` structure that combines an index and a generation
 * for safe resource management. The `Handle` structure includes an index that
 * can be used to reference a resource in a pool or array, and a generation that
 * can be used to detect stale or invalid handles. This structure is intended
 * to be used as a lightweight and efficient way to manage resources in the
 * engine, allowing for safe referencing and automatic detection of invalid or
 * stale references without the need for complex pointer management or reference
 * counting.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include "types/nyTypes.hpp"

namespace nyEngineSDK
{
  /**
   * @brief A handle structure that combines an index and a generation for safe
   *        resource management.
   */
  struct Handle
  {
    u32 index = 0xFFFFFFFFu;
    u32 generation = 0;
  };

  /**
   * @brief A constant representing an invalid handle, where the index is set to
   *        0xFFFFFFFFu and the generation is set to 0.
   */
  inline constexpr Handle kInvalidHandle{ 0xFFFFFFFFu, 0u };

  /**
   * @brief Checks if a given handle is valid by verifying that its index is not
   *        equal to 0xFFFFFFFFu.
   */
  inline bool
  isValid(const Handle& h) noexcept
  {
    return h.index != 0xFFFFFFFFu;
  }

  /**
   * @brief Compares two handles for equality by checking if both their index
   *        and generation are the same.
   */
  inline bool
  operator==(const Handle& a, const Handle& b) noexcept
  {
    return (a.index == b.index) && (a.generation == b.generation);
  }

  /**
   * @brief Compares two handles for inequality by negating the result of the
   *        equality operator.
   */
  inline bool
  operator!=(const Handle& a, const Handle& b) noexcept
  {
    return !(a == b);
  }
} // namespace nyEngineSDK