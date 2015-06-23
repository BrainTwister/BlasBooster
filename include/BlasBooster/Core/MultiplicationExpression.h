// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MULTIPLICATIONEXPRESSION_H_
#define MULTIPLICATIONEXPRESSION_H_

#include "BlasBooster/Core/Matrix.h"

namespace BlasBooster {

/// Expression template for matrix-matrix multiplication
template <class M1, class T1,
          class M2, class T2, class P>
class MatrixMultExp
{
public:

    MatrixMultExp(Matrix<M1,T1,P> const& A, Matrix<M2,T2,P> const& B)
     : A(A), B(B)
    {}

    template <class Interface>
    Matrix<decltype(M1() * M2()), decltype(T1() * T2()), P> execute() const
    {
        Matrix<decltype(M1() * M2()), decltype(T1() * T2()), P> C;
        Interface::MultiplicationFunctor<M1,T1,P,M2,T2,P, decltype(M1() * M2()), decltype(T1() * T2()), P>()(A,B,C);
        return C;
    }

private:

    Matrix<M1,T1,P> const& A;
    Matrix<M2,T2,P> const& B;

};

/// Operator for Matrix multiplication
template <class M1, class T1,
          class M2, class T2, class P>
inline MatrixMultExp<M1,T1,M2,T2,P> operator * (Matrix<M1,T1,P> const& A, Matrix<M2,T2,P> const& B)
{
    return MatrixMultExp<M1,T1,M2,T2,P>(A,B);
}

} // namespace BlasBooster

#endif /* MULTIPLICATIONEXPRESSION_H_ */

