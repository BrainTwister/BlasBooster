#pragma once

namespace BlasBooster {

template <class M1, class T1, class P1, class M2, class T2, class P2>
double getMaximalDeviation(Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B)
{
    double maximalDeviation(0.0);
    typename Matrix<M1,T1,P1>::const_iterator iterACur(A.begin()), iterAEnd(A.end());
    typename Matrix<M2,T2,P2>::const_iterator iterBCur(B.begin());
    for ( ; iterACur != iterAEnd; ++iterACur, ++iterBCur )
    {
        maximalDeviation = std::max(maximalDeviation, std::abs(*iterACur - *iterBCur));
    }
    return maximalDeviation;
}

template <class M1, class T1, class P1, class M2, class T2, class P2>
double getRootMeanSquareDeviation(Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B)
{
    double meanSquare(0.0);
    typename Matrix<M1,T1,P1>::const_iterator iterACur(A.begin()), iterAEnd(A.end());
    typename Matrix<M2,T2,P2>::const_iterator iterBCur(B.begin());
    for ( ; iterACur != iterAEnd; ++iterACur, ++iterBCur )
    {
        meanSquare += std::pow(*iterACur - *iterBCur, 2);
    }
    return std::sqrt(meanSquare/(A.getNbRows()*A.getNbColumns()));
}

} // namespace BlasBooster
