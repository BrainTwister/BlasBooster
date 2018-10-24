#pragma once

#include "blaze/util/Memory.h"

namespace BlasBooster {

template <typename T>
T* allocate(size_t size)
{
    return blaze::allocate<T>(size);
}

template <typename T>
void deallocate(T* address) noexcept
{
    blaze::deallocate(address);
}

} // namespce BlasBooster
