#ifndef TYPECHECKER_H_
#define TYPECHECKER_H_

#include <cstddef>

namespace BlasBooster {

struct TypeChecker
{
    TypeChecker(size_t typeIndex) : typeIndex_(typeIndex) {}

    template <class T>
    bool operator()( T* = 0 ) const
    {
        return T::typeIndex_ == typeIndex_;
    }

    size_t typeIndex_;
};

} // namespace BlasBooster

#endif /* TYPECHECKER_H_ */
