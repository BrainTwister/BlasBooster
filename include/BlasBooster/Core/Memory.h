#pragma once

#include "blaze/util/Memory.h"

namespace BlasBooster {

template <typename T>
T* allocate(size_t size)
{
    //return new T[size];
    return blaze::allocate<T>(size);
}

template <typename T>
void deallocate(T* memory) noexcept
{
	//delete [] memory;
    blaze::deallocate(memory);
}

} // namespce BlasBooster
