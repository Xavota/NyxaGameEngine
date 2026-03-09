#include "memory/nyAllocator.hpp"

#include <atomic>
#include <cstdlib>

#include "macros/nyMacros.hpp"
#include "macros/nyPlatform.hpp"


#if NY_OS_WINDOWS
  #include <malloc.h>
#endif

namespace nyEngineSDK
{
  namespace
  {
    class MallocAllocator final : public Allocator
    {
     public:
      NY_NODISCARD void*
      allocate(usize sizeBytes, usize alignmentBytes) noexcept override
      {
        if (sizeBytes == 0)
        {
          sizeBytes = 1;
        }

        if (alignmentBytes == 0)
        {
          alignmentBytes = 16;
        }

        #if NY_OS_WINDOWS
          return _aligned_malloc(sizeBytes, alignmentBytes);
        #else
          void* p = nullptr;

          // posix_memalign requires alignment to be a multiple of sizeof(void*)
          // and a power of two. Caller should pass sane alignment.
          int res = posix_memalign(&p, alignmentBytes, sizeBytes);
          if (res != 0)
          {
            return nullptr;
          }
          return p;
        #endif
      }

      void
      deallocate(void* p) noexcept override
      {
        #if NY_OS_WINDOWS
          _aligned_free(p);
        #else
          std::free(p);
        #endif
      }

      NY_NODISCARD void*
      reallocate(void* p, usize newSizeBytes, usize alignmentBytes) noexcept override
      {
        if (newSizeBytes == 0)
        {
          newSizeBytes = 1;
        }

        if (alignmentBytes == 0)
        {
          alignmentBytes = 16;
        }

        #if NY_OS_WINDOWS
          return _aligned_realloc(p, newSizeBytes, alignmentBytes);
        #else
          // Portable aligned realloc is not available on all platforms.
          // Keep it simple for v0: alloc new + caller copies if needed.
          (void)p;
          (void)newSizeBytes;
          (void)alignmentBytes;
          return nullptr;
        #endif
      }
    };

    MallocAllocator gMallocAllocator{};

    std::atomic<Allocator*> gDefaultAllocator{ &gMallocAllocator };

  } // namespace

  Allocator&
  getMallocAllocator() noexcept
  {
    return gMallocAllocator;
  }

  void
  setDefaultAllocator(Allocator* allocator) noexcept
  {
    if (!allocator)
    {
      allocator = &gMallocAllocator;
    }

    gDefaultAllocator.store(allocator, std::memory_order_relaxed);
  }

  Allocator*
  getDefaultAllocator() noexcept
  {
    return gDefaultAllocator.load(std::memory_order_relaxed);
  }

  void*
  alloc(usize sizeBytes, usize alignmentBytes) noexcept
  {
    Allocator* a = getDefaultAllocator();
    NY_ASSERT(a != nullptr);
    return a->allocate(sizeBytes, alignmentBytes);
  }

  void
  free(void* p) noexcept
  {
    Allocator* a = getDefaultAllocator();
    NY_ASSERT(a != nullptr);
    a->deallocate(p);
  }

} // namespace u0