/******************************************************************************/
/**
 * @file    nyMemory.hpp
 * @author  Dalia Castellanos
 * @date    23/02/2026
 * @brief   Defines memory management utilities for the Utilities library.
 * 
 * Defines utility functions for memory management in the Utilities library,
 * including functions to check if a number is a power of two, align values up
 * to a specified alignment, and allocate/deallocate objects using a specified
 * allocator or the default allocator.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <new>
#include <utility>

#include "memory/nyAllocator.hpp"
#include "macros/nyMacros.hpp"
#include "types/nyTypes.hpp"

namespace nyEngineSDK
{
  /**
   * @brief  Checks if a number is a power of two.
   * @param  x  The number to check.
   * @return `true` if `x` is a power of two, and `false` otherwise. Note that
   *         zero is not considered a power of two but one is.
   * @bug	   No known bugs.
   */
  inline bool
  isPowerOfTwo(usize x) noexcept
  {
    return (x != 0) && ((x & (x - 1)) == 0);
  }

  /**
   * @brief  Aligns a value up to the nearest multiple of the specified alignment.
   * @param  value      The value to align.
   * @param  alignment  The alignment to align to, in bytes. This must be a
   *                    power of two and not zero.
   * @return The smallest value greater than or equal to `value` that is a
   *         multiple of `alignment`.
   * @bug	   No known bugs.
   */
  inline usize
  alignUp(usize value, usize alignment) noexcept
  {
    NY_ASSERT(isPowerOfTwo(alignment));
    return (value + (alignment - 1)) & ~(alignment - 1);
  }

  /**
   * @brief  Allocates memory for an object of type `T` using the specified
   *         allocator, and constructs the object in-place with the given
   *         arguments.
   * @param  allocator  The allocator to use for memory allocation. This
   *                    allocator must not be `nullptr`.
   * @param  args       The arguments to forward to the constructor of `T`.
   * @return A pointer to the newly allocated and constructed object of type
   *         `T`, or `nullptr` if allocation fails.
   * @bug	   No known bugs.
   */
  template <class T, class... Args>
  inline T*
  allocNew(Allocator& allocator, Args&&... args) noexcept
  {
    void* mem = allocator.allocate(sizeof(T), alignof(T));

    if (!mem)
    {
      return nullptr;
    }

    return new (mem) T(std::forward<Args>(args)...);
  }

  /**
   * @brief  Destroys an object of type `T` and deallocates the memory used by
   *         the object using the specified allocator.
   * @param  allocator  The allocator to use for memory deallocation. This
   *                    allocator must not be `nullptr`.
   * @param  p          A pointer to the object to destroy and deallocate.
   *                    This pointer must have been returned by a previous call
   *                    to `allocNew` using the same allocator, and must not
   *                    have already been deallocated.
   * @bug	   No known bugs.
   */
  template <class T>
  inline void
  allocDelete(Allocator& allocator, T* p) noexcept
  {
    if (!p)
    {
      return;
    }

    p->~T();
    allocator.deallocate(p);
  }

  /**
   * @brief  Allocates memory for an object of type `T` using the current default
   *         allocator, and constructs the object in-place with the given arguments.
   * @param  args  The arguments to forward to the constructor of `T`.
   * @return A pointer to the newly allocated and constructed object of type
   *         `T`, or `nullptr` if allocation fails.
   * @bug	   No known bugs.
   */
  template <class T, class... Args>
  inline T*
  newDefault(Args&&... args) noexcept
  {
    Allocator* allocator = getDefaultAllocator();
    NY_ASSERT(allocator != nullptr);
    return allocNew<T>(*allocator, std::forward<Args>(args)...);
  }

  /**
   * @brief  Destroys an object of type `T` and deallocates the memory used by
   *         the object using the current default allocator.
   * @param  p  A pointer to the object to destroy and deallocate. This pointer
   *            must have been returned by a previous call to `newDefault`, and
   *            must not have already been deallocated.
   * @bug	   No known bugs.
   */
  template <class T>
  inline void
  deleteDefault(T* p) noexcept
  {
    Allocator* allocator = getDefaultAllocator();
    NY_ASSERT(allocator != nullptr);
    allocDelete(*allocator, p);
  }
} // namespace nyEngineSDK