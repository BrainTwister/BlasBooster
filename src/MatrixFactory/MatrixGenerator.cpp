#include "BlasBooster/MatrixFactory/MatrixGenerator.h"
#include <random>

namespace BlasBooster {

Matrix<Dense,double> MatrixGenerator::operator()() const
{
    Matrix<Dense,double> matrix(nbRows,nbColumns);

    std::default_random_engine e(settings.seed);
    std::uniform_real_distribution<> d1(settings.minValue, settings.maxValue);
    std::uniform_int_distribution<> d2(0, 1);

    for (Matrix<Dense,double>::iterator iterCur(matrix.begin()),
        iterEnd(matrix.end()); iterCur != iterEnd; ++iterCur)
    {
        *iterCur = (d2(e) ? -1 : 1) * pow(10,-d1(e));
    }

    return matrix;
}

} // namespace BlasBooster
