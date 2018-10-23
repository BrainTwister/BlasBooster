#pragma once

#include <cstdlib>
#include <new>

#if WIN64_PLATFORM || MINGW64_PLATFORM || MINGW32_PLATFORM
  #include <malloc.h>
#endif

namespace BlasBooster {

using byte_t = unsigned char;

inline byte_t* allocate_backend(size_t size, size_t alignment)
{
   void* raw( nullptr );

#if WIN64_PLATFORM || MINGW64_PLATFORM
   raw = _aligned_malloc(size, alignment);
   if(raw == nullptr) {
#elif MINGW32_PLATFORM
   raw = __mingw_aligned_malloc(size, alignment);
   if(raw == nullptr) {
#else
   if(posix_memalign(&raw, alignment, size)) {
#endif
	  throw std::bad_alloc();
   }

   return reinterpret_cast<byte_t*>(raw);
}

template <typename T>
T* allocate(size_t size)
{
   constexpr size_t alignment = std::alignment_of<float>::value;
   return reinterpret_cast<T*>(allocate_backend(size * sizeof(T), alignment));
   //return new T[size];
}

inline void deallocate_backend(const void* address) noexcept
{
#if WIN64_PLATFORM || MINGW64_PLATFORM
   _aligned_free( const_cast<void*>( address ) );
#elif MINGW32_PLATFORM
   __mingw_aligned_free( const_cast<void*>( address ) );
#else
   free(const_cast<void*>(address));
#endif
}

template <typename T>
void deallocate(T* address) noexcept
{
   if(address == nullptr) return;
   deallocate_backend(address);
}

} // namespce BlasBooster
