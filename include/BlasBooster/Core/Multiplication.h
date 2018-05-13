#pragma once

#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Utilities/wrong_t.h"

namespace BlasBooster {

/// Dummy operator to define resulting matrix type by multiplication by using decltype
Dense operator * (Dense, Dense);
Dense operator * (Dense, Sparse);
Dense operator * (Sparse, Dense);
Sparse operator * (Sparse, Sparse);
Zero operator * (Dense, Zero);
Zero operator * (Zero, Dense);
Zero operator * (Sparse, Zero);
Zero operator * (Zero, Sparse);
Zero operator * (Zero, Zero);

template <class T> Parameter<T, ColumnMajor> operator * (Parameter<T, ColumnMajor>, Parameter<T, ColumnMajor>);
template <class T> Parameter<T, ColumnMajor> operator * (Parameter<T, ColumnMajor>, Parameter<T, RowMajor>);
template <class T> Parameter<T, ColumnMajor> operator * (Parameter<T, RowMajor>, Parameter<T, ColumnMajor>);
template <class T> Parameter<T, ColumnMajor> operator * (Parameter<T, RowMajor>, Parameter<T, RowMajor>);

/// Primary template matrix multiplication must never be instantiated.
template <class M1, class T1, class P1,
          class M2, class T2, class P2,
          class M3, class T3, class P3,
          class Interface>
struct MultiplicationFunctor
{
    static_assert(wrong_t<M1>::value, "Primary template must not be instantiated.");
};

} // namespace BlasBooster
