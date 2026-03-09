/******************************************************************************/
/**
 * @file    nyAllocator.hpp
 * @author  Dalia Castellanos
 * @date    20/02/2026
 * @brief   Defines the Allocator interface and related functions for memory management.
 * 
 * Defines an abstract `Allocator` class that serves as the interface for memory
 * allocation and deallocation in the Utilities library. This class allows for
 * custom memory management strategies to be implemented by deriving from
 * `Allocator` and implementing the `allocate` and `deallocate` methods.
 * Additionally, it provides a default global allocator that uses the standard
 * `malloc` and `free` functions, and functions to get and set the default
 * allocator used by the library for memory management.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include "macros/nyApi.hpp"
#include "types/nyTypes.hpp"

namespace nyEngineSDK
{
  /**
   * @brief  Abstract base class for memory allocators. Defines the interface
   *         for allocating, deallocating, and optionally reallocating memory.
   * @bug	   No known bugs.
   */
  class Allocator
  {
   public:
    /**
     * @brief  Virtual destructor.
     * @bug	   No known bugs.
     */
    virtual
    ~Allocator() noexcept = default;

    /**
     * @brief  Allocates a block of memory of the specified size and alignment.
     * @param  sizeBytes       The size of the memory block to allocate, in
     *                         bytes. By default, this should not be zero,
     *                         unless overwritten to allow it.
     * @param  alignmentBytes  The alignment requirement for the allocated
     *                         memory, in bytes. By default, this should not be
     *                         zero, unless overwritten to allow it.
     * @return A pointer to the allocated memory block, or `nullptr` if
     *         allocation fails.
     * @bug	   No known bugs.
     */
    NY_NODISCARD virtual void*
    allocate(usize sizeBytes, usize alignmentBytes) noexcept = 0;

    /**
     * @brief  Deallocates a previously allocated block of memory.}
     * @param  p   A pointer to the memory block to deallocate. This pointer must
     *             have been returned by a previous call to `allocate` on the same
     *             allocator instance, and must not have already been deallocated.
     * @bug	   No known bugs.
     */
    virtual void
    deallocate(void* p) noexcept = 0;

    /**
     * @brief  Reallocates a previously allocated block of memory to a new size
     *         and alignment.
     * @param  p               A pointer to the memory block to reallocate. This
     *                         pointer must have been returned by a previous
     *                         call to `allocate` on the same allocator instance,
     *                         and must not have already been deallocated.
     * @param  newSizeBytes    The new size of the memory block, in bytes. By
     *                         default, this should not be zero, unless
     *                         overwritten to allow it.
     * @param  alignmentBytes  The new alignment requirement for the memory
     *                         block, in bytes. By default, this should not be
     *                         zero, unless overwritten to allow it.
     * @return A pointer to the reallocated memory block, which may be the same
     *         as the input pointer `p` if the allocator can resize in place, or
     *         a new pointer if the allocator needs to move the block. If
     *         reallocation fails, returns `nullptr` and the original block
     *         remains unchanged.
     * @bug	   No known bugs.
     */
    NY_NODISCARD virtual void*
    reallocate(void* p, usize newSizeBytes, usize alignmentBytes) noexcept
    {
      (void)p;
      (void)newSizeBytes;
      (void)alignmentBytes;
      return nullptr;
    }
  };

  /**
   * @brief  Returns a reference to a global allocator that uses the standard
   *         malloc/free functions for memory management. This allocator is used
   *         as the default allocator for the library, but can be overridden by
   *         calling `setDefaultAllocator`. The returned allocator instance is
   *         thread-safe and can be used concurrently from multiple threads.
   * @return A reference to a global allocator that uses malloc/free for memory
   *         management.
   * @bug	   No known bugs.
   */
  NY_API NY_NODISCARD Allocator&
  getMallocAllocator() noexcept;

  /**
   * @brief  Sets the default allocator to be used by the library when
   *         allocating memory. If `nullptr` is passed, the default allocator
   *         will be reset to the global malloc allocator.
   * @param  allocator   A pointer to the allocator to set as the default. If
   *                     `nullptr`, the default allocator will be reset to the
   *                     global malloc allocator.
   * @bug	   No known bugs.
   */
  NY_API void
  setDefaultAllocator(Allocator* allocator) noexcept;

  /**
   * @brief  Returns a pointer to the current default allocator used by the
   *         library for memory allocation. This allocator is used by the
   *         `alloc` and `free` functions to manage memory. If no custom
   *         allocator has been set using `setDefaultAllocator`, this will
   *         return a pointer to the global malloc allocator.
   * @return A pointer to the current default allocator used by the library for
   *         memory allocation.
   * @bug	   No known bugs.
   */
  NY_API NY_NODISCARD Allocator*
  getDefaultAllocator() noexcept;

  /**
   * @brief  Allocates a block of memory of the specified size and alignment
   *         using the current default allocator. This is a convenience function
   *         that forwards to the `allocate` method of the default allocator.
   *         The allocated memory should be freed using the `free` function,
   *         which will forward to the `deallocate` method of the default allocator.
   * @param  sizeBytes       The size of the memory block to allocate, in bytes.
   *                         By default, this should not be zero, unless
   *                         overwritten to allow it.
   * @param  alignmentBytes  The alignment requirement for the allocated memory,
   *                         in bytes. By default, this should not be zero,
   *                         unless overwritten to allow it.
   * @return A pointer to the allocated memory block, or `nullptr` if allocation
   *         fails.
   * @bug	   No known bugs.
   */
  NY_API NY_NODISCARD void*
  alloc(usize sizeBytes, usize alignmentBytes = 16) noexcept;

  /**
   * @brief  Frees a block of memory previously allocated with the `alloc`
   *         function using the current default allocator. This is a
   *         convenience function that forwards to the `deallocate` method
   *         of the default allocator.
   * @param  p   A pointer to the memory block to free. This pointer must have
   *             been returned by a previous call to `alloc` using the same
   *             default allocator, and must not have already been freed.
   * @bug	   No known bugs.
   */
  NY_API void
  free(void* p) noexcept;
} // namespace nyEngineSDK