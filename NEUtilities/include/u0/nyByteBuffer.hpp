/*****************************************************************************/
/**
 * @file    nyByteBuffer.hpp
 * @author  Dalia Castellanos
 * @date    25/02/2026
 * @brief   Defines the ByteBuffer class for managing a contiguous block of memory.
 * 
 * Defines a simple `ByteBuffer` class that manages a contiguous block of memory
 * for storing raw bytes. The `ByteBuffer` class provides functionality for
 * resizing, appending, and releasing the buffer, as well as managing its own
 * memory using a provided allocator.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include <cstring>
#include <utility>

#include "u0/nyAllocator.hpp"
#include "u0/nyMacros.hpp"
#include "u0/nyTypes.hpp"

namespace nyEngineSDK
{
  /*
   * @brief  A simple byte buffer class that manages a contiguous block of memory
   *         for storing raw bytes. The ByteBuffer class provides functionality
   *         for resizing, appending, and releasing the buffer, as well as
   *         managing its own memory using a provided allocator.
   * @bug	   No known bugs.
   */
  class ByteBuffer
  {
   public:
    /*
     * @brief  Constructs an empty ByteBuffer with no allocator. The buffer will
     *         be invalid until an allocator is set using `setAllocator`.
     * @bug	   No known bugs.
     */
    ByteBuffer() noexcept
      : mAllocator(nullptr), mData(nullptr), mSize(0), mCapacity(0) {}

    /*
     * @brief  Constructs an empty ByteBuffer with the specified allocator. The
     *         buffer will be valid and ready for use, but will have no
     *         allocated memory until `resize` or `append` is called.
     * @param  allocator  The allocator to use for managing the buffer's memory.
     * @bug	   No known bugs.
     */
    explicit ByteBuffer(Allocator& allocator) noexcept
      : mAllocator(&allocator), mData(nullptr), mSize(0), mCapacity(0) {}

    /*
     * @brief  Constructs a ByteBuffer with the specified allocator and initial
     *         size. The buffer will be valid and ready for use, with memory
     *         allocated to hold `sizeBytes` bytes. The buffer will be
     *         zero-initialized.
     * @param  allocator       The allocator to use for managing the buffer's
     *                         memory.
     * @param  sizeBytes       The initial size of the buffer in bytes. If zero,
     *                         the buffer will be empty but still valid.
     * @param  alignmentBytes  The alignment requirement for the allocated memory,
     *                         in bytes. This must be a power of two and not zero.
     * @bug	   No known bugs.
     */
    ByteBuffer(Allocator& allocator, usize sizeBytes, usize alignmentBytes = 16) noexcept
      : mAllocator(&allocator), mData(nullptr), mSize(0), mCapacity(0)
    {
      resize(sizeBytes, alignmentBytes);
    }

    /*
     * @brief  Deleted copy constructor and copy assignment operator to prevent
     *         copying of the ByteBuffer, as it manages its own memory and
     *         should not be copied implicitly.
     * @bug	   No known bugs.
     */
    ByteBuffer(const ByteBuffer&) = delete;

    /*
     * @brief  Deleted copy assignment operator to prevent copying of the ByteBuffer,
     *         as it manages its own memory and should not be copied implicitly.
     * @bug	   No known bugs.
     */
    ByteBuffer&
    operator=(const ByteBuffer&) = delete;

    /*
     * @brief  Move constructor and move assignment operator to allow efficient
     *         transfer of ownership of the buffer's memory from one ByteBuffer
     *         instance to another. After the move, the source ByteBuffer will
     *         be left in a valid but empty state, with no allocated memory and
     *         a null allocator pointer.
     * @bug	   No known bugs.
     */
    ByteBuffer(ByteBuffer&& other) noexcept
      : mAllocator(other.mAllocator), mData(other.mData),
        mSize(other.mSize), mCapacity(other.mCapacity)
    {
      other.mAllocator = nullptr;
      other.mData = nullptr;
      other.mSize = 0;
      other.mCapacity = 0;
    }

    /*
     * @brief  Move assignment operator to allow efficient transfer of ownership
     *         of the buffer's memory from one ByteBuffer instance to another.
     *         After the move, the source ByteBuffer will be left in a valid but
     *         empty state, with no allocated memory and a null allocator pointer.
     *         If the destination ByteBuffer already has allocated memory, it
     *         will be deallocated before taking ownership of the source's memory.
     * @bug	   No known bugs.
     */
    ByteBuffer&
    operator=(ByteBuffer&& other) noexcept
    {
      if (this == &other)
      {
        return *this;
      }

      reset();

      mAllocator = other.mAllocator;
      mData = other.mData;
      mSize = other.mSize;
      mCapacity = other.mCapacity;

      other.mAllocator = nullptr;
      other.mData = nullptr;
      other.mSize = 0;
      other.mCapacity = 0;

      return *this;
    }

    /*
     * @brief  Destructor that deallocates any allocated memory and resets the
     *         buffer to an empty state. If the buffer has allocated memory, it
     *         will be deallocated using the associated allocator before the
     *         buffer is destroyed.
     * @bug	   No known bugs.
     */
    ~ByteBuffer() noexcept
    {
      reset();
    }

    /*
     * @brief  Checks if the ByteBuffer is valid, which means it has an
     *         associated allocator.
     * @return `true` if the ByteBuffer has a valid allocator and can be used
     *         for memory operations, or `false` if it does not have an
     *         allocator and cannot be used for memory operations until an
     *         allocator is set.
     * @bug	   No known bugs.
     */
    bool
    isValid() const noexcept
    {
      return (mAllocator != nullptr);
    }

    /*
     * @brief  Sets the allocator to be used for managing the buffer's memory.
     *         This function must be called before any memory operations (like
     *         `resize` or `append`) can be performed on the ByteBuffer. The
     *         ByteBuffer must not have any allocated memory when this function
     *         is called, as changing the allocator while memory is allocated
     *         would lead to undefined behavior.
     * @param  allocator  The allocator to set for managing the buffer's memory.
     * @bug	   No known bugs.
     */
    void
    setAllocator(Allocator& allocator) noexcept
    {
      NY_ASSERT(mData == nullptr);
      mAllocator = &allocator;
    }

    /*
     * @brief  Returns a pointer to the raw byte data stored in the buffer. The
     *         returned pointer is valid for reading and writing up to `size()`
     *         bytes. If the buffer is empty, the returned pointer may be
     *         `nullptr` or may point to a valid memory location, but should not
     *         be dereferenced without first checking that the buffer is not empty.
     * @return A pointer to the raw byte data stored in the buffer, or `nullptr`
     *         if the buffer is empty.
     * @bug	   No known bugs.
     */
    byte*
    data() noexcept
    {
      return static_cast<byte*>(mData);
    }

    /*
     * @brief  Returns a const pointer to the raw byte data stored in the buffer.
     *         The returned pointer is valid for reading up to `size()` bytes.
     *         If the buffer is empty, the returned pointer may be `nullptr` or
     *         may point to a valid memory location, but should not be
     *         dereferenced without first checking that the buffer is not empty.
     * @return A const pointer to the raw byte data stored in the buffer, or
     *         `nullptr` if the buffer is empty.
     * @bug	   No known bugs.
     */
    const byte*
    data() const noexcept
    {
      return static_cast<const byte*>(mData);
    }

    /*
     * @brief  Returns the current size of the buffer in bytes, which represents
     *         the number of bytes that have been allocated and are currently in
     *         use.
     * @return The current size of the buffer in bytes, or zero if the buffer
     *         is empty.
     * @bug	   No known bugs.
     */
    usize
    size() const noexcept
    {
      return mSize;
    }

    /*
     * @brief  Returns the current capacity of the buffer in bytes, which
     *         represents the total number of bytes that have been allocated for
     *         the buffer. The capacity may be greater than or equal to the size,
     *         depending on how the buffer has been resized or appended to.
     * @return The current capacity of the buffer in bytes, or zero if the
     *         buffer has no allocated memory.
     * @bug	   No known bugs.
     */
    usize
    capacity() const noexcept
    {
      return mCapacity;
    }

    /*
     * @brief  Checks if the buffer is empty, which means it has a size of zero.
     *         An empty buffer may still have allocated memory (capacity greater
     *         than zero), but it does not contain any valid data.
     * @return `true` if the buffer is empty (size is zero), or `false` if the
     *         buffer contains any data (size greater than zero).
     * @bug	   No known bugs.
     */
    bool
    empty() const noexcept
    {
      return mSize == 0;
    }

    /*
     * @brief  Clears the buffer by setting its size to zero. This does not
     *         deallocate any allocated memory, so the capacity remains unchanged.
     *         If you want to completely reset the buffer and deallocate
     *         all memory, use the `reset` function instead.
     * @bug	   No known bugs.
     */
    void
    clear() noexcept
    {
      mSize = 0;
    }

    /*
     * @brief  Resets the buffer by deallocating any allocated memory and setting
     *         the size and capacity to zero. If the buffer has allocated
     *         memory, it will be deallocated using the associated allocator
     *         before the buffer is reset.
     * @bug	   No known bugs.
     */
    void
    reset() noexcept
    {
      if (mData)
      {
        NY_ASSERT(mAllocator != nullptr);
        mAllocator->deallocate(mData);
      }

      mData = nullptr;
      mSize = 0;
      mCapacity = 0;
    }

    /*
     * @brief  Reserves memory for the buffer to hold at least `newCapacityBytes`
     *         bytes. If the current capacity is already sufficient, this
     *         function does nothing and returns `true`. If the current capacity
     *         is less than `newCapacityBytes`, this function attempts to
     *         allocate a new block of memory with the specified capacity and
     *         alignment, copies any existing data to the new block, and
     *         deallocates the old block. If allocation fails, the buffer
     *         remains unchanged and the function returns `false`.
     * @param  newCapacityBytes  The new capacity to reserve for the buffer,
     *                           in bytes. This must be greater than the current
     *                           capacity for the function to attempt to reserve
     *                           new memory.
     * @param  alignmentBytes    The alignment requirement for the allocated
     *                           memory, in bytes. This must be a power of two
     *                           and not zero.
     * @return `true` if the buffer has at least `newCapacityBytes` of capacity
     *         after the function call (either because it already had sufficient
     *         capacity or because it successfully reserved new memory), or
     *         `false` if the function failed to reserve the requested capacity
     *         due to allocation failure.
     * @bug	   No known bugs.
     */
    bool
    reserve(usize newCapacityBytes, usize alignmentBytes = 16) noexcept
    {
      NY_ASSERT(mAllocator != nullptr);

      if (newCapacityBytes <= mCapacity)
      {
        return true;
      }

      void* newMem = mAllocator->allocate(newCapacityBytes, alignmentBytes);
      if (!newMem)
      {
        return false;
      }

      if (mData && mSize > 0)
      {
        std::memcpy(newMem, mData, mSize);
        mAllocator->deallocate(mData);
      }

      mData = newMem;
      mCapacity = newCapacityBytes;
      return true;
    }

    /*
     * @brief  Resizes the buffer to hold `newSizeBytes` bytes. 
     *         - If the new size is greater than the current capacity, this
     *           function will attempt to reserve new memory with the specified
     *           size and alignment.
     *         - If the new size is less than or equal to the current capacity,
     *           this function simply updates the size without changing the capacity.
     *         - If the new size is zero, the buffer is cleared but the capacity
     *           remains unchanged.
     *         - If the new size is equal to the current size, this function
     *           does nothing and returns `true`.
     *         - If the function fails to reserve new memory when needed, the
     *           buffer remains unchanged and the function returns `false`.
     * @param  newSizeBytes    The new size of the buffer in bytes. This can be zero
     *                         to clear the buffer, or any value up to the current
     *                         capacity without needing to reserve new memory.
     * @param  alignmentBytes  The alignment requirement for the allocated memory
     *                         if new memory needs to be reserved, in bytes.
     *                         This must be a power of two and not zero.
     * @return `true` if the buffer has been resized to `newSizeBytes` (either
     *         because it already had sufficient capacity or because it
     *         successfully reserved new memory), or `false` if the function
     *         failed to resize the buffer due to allocation failure when trying
     *         to reserve new memory.
     * @bug	   No known bugs.
     */
    bool
    resize(usize newSizeBytes, usize alignmentBytes = 16) noexcept
    {
      if (newSizeBytes == mSize)
      {
        return true;
      }

      if (newSizeBytes == 0)
      {
        reset();
        return true;
      }

      NY_ASSERT(mAllocator != nullptr);

      if (newSizeBytes > mCapacity)
      {
        if (!reserve(newSizeBytes, alignmentBytes))
        {
          return false;
        }
      }

      mSize = newSizeBytes;
      return true;
    }

    /*
     * @brief  Appends raw byte data to the end of the buffer. If the new total
     *         size after appending exceeds the current capacity, this function
     *         will attempt to reserve new memory with the specified alignment
     *         to accommodate the new size.
     * @param  src             A pointer to the raw byte data to append to the
     *                         buffer. This pointer must be valid and point to
     *                         at least `srcSizeBytes` bytes of readable memory.
     * @param  srcSizeBytes    The size of the source data to append, in bytes.
     *                         This can be zero, in which case the function does
     *                         nothing and returns `true`.
     * @param  alignmentBytes  The alignment requirement for the allocated memory
     *                         if new memory needs to be reserved to accommodate
     *                         the new size after appending, in bytes. This must
     *                         be a power of two and not zero.
     * @return `true` if the source data was successfully appended to the buffer
     *         (either because it already had sufficient capacity or because it
     *         successfully reserved new memory), or `false` if the function
     *         failed to append the data due to allocation failure when trying
     *         to reserve new memory.
     * @bug	   No known bugs.
     */
    bool
    append(const void* src, usize srcSizeBytes, usize alignmentBytes = 16) noexcept
    {
      if (srcSizeBytes == 0)
      {
        return true;
      }

      NY_ASSERT(src != nullptr);

      usize oldSize = mSize;
      usize newSize = oldSize + srcSizeBytes;

      if (!resize(newSize, alignmentBytes))
      {
        return false;
      }

      std::memcpy(static_cast<byte*>(mData) + oldSize, src, srcSizeBytes);
      return true;
    }

    /*
     * @brief  Releases ownership of the buffer's memory and returns a pointer
     *         to it. After calling this function, the ByteBuffer will be left
     *         in an empty state with no allocated memory, and the caller is
     *         responsible for managing the lifetime of the returned memory
     *         block, including deallocating it using the same allocator that
     *         was used to allocate it when the caller is done with it. This
     *         function is useful for transferring ownership of the buffer's
     *         memory to another part of the program without copying it.
     * @return A pointer to the raw byte data that was managed by the buffer, or
     *         `nullptr` if the buffer was empty. After this call, the buffer
     *         will be reset to an empty state with no allocated memory, and the
     *         caller is responsible for managing the lifetime of the returned
     *         memory block, including deallocating it using the same allocator
     *         that was used to allocate it when the caller is done with it.
     * @bug	   No known bugs.
     */
    void*
    release() noexcept
    {
      void* out = mData;
      mData = nullptr;
      mSize = 0;
      mCapacity = 0;
      return out;
    }

   private:
    /*
     * @brief  Pointer to the allocator used for managing the buffer's memory.
     *         The allocator is responsible for allocating, deallocating, and
     *         potentially reallocating the memory used by the buffer.
     */
    Allocator* mAllocator;
    /*
     * @brief  Pointer to the raw byte data stored in the buffer. This pointer
     *         is valid for reading and writing up to `size()` bytes, and the
     *         memory it points to is managed by the buffer and should not be
     *         accessed directly outside of the buffer's member functions.
     */
    void* mData;
    /*
     * @brief  The current size of the buffer in bytes, which represents the
     *         number of bytes that have been allocated and are currently in use.
     */
    usize mSize;
    /*
     * @brief  The current capacity of the buffer in bytes, which represents the
     *         total number of bytes that have been allocated for the buffer.
     *         The capacity may be greater than or equal to the size, depending
     *         on how the buffer has been resized or appended to.
     */
    usize mCapacity;
  };
} // namespace nyEngineSDK