#include "BlasBooster/MatrixFactory/MatrixGenerator.h"
#include <random>

using namespace std;

namespace BlasBooster {

Matrix<Dense,double> MatrixGenerator::operator()() const
{
	Matrix<Dense,double> matrix(nbRows,nbColumns);

	default_random_engine e(settings.seed_);
	uniform_real_distribution<> d1(settings.minValue_,settings.maxValue_);
	uniform_int_distribution<> d2(0,1);

	for (Matrix<Dense,double>::iterator iterCur(matrix.begin()),
		iterEnd(matrix.end()); iterCur != iterEnd; ++iterCur)
	{
		*iterCur = (d2(e) ? -1 : 1) * pow(10,-d1(e));
	}

	return matrix;
}

} // namespace BlasBooster
