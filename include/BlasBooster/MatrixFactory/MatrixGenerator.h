#ifndef MATRIXGENERATOR_H_
#define MATRIXGENERATOR_H_

#include "BlasBooster/MatrixFactory/MatrixFactory.h"
#include "BrainTwister/Settings.h"

namespace BlasBooster {

class MatrixGenerator : public MatrixFactory
{
public:

	BRAINTWISTER_SETTINGS( Settings,\
		(( unsigned int, seed, 0 ))\
	    (( double, occupation, 1.0 ))\
	    (( double, minValue, 0.0 ))\
	    (( double, maxValue, 9.0 ))\
	)

	MatrixGenerator(size_t nbRows, size_t nbColumns, Settings const& settings = Settings())
	 : MatrixFactory(nbRows, nbColumns), settings(settings)
	{}

	virtual ~MatrixGenerator() {}

    Matrix<Dense,double> operator()() const;

private:

	Settings settings;

};

} // namespace BlasBooster

#endif /* MATRIXGENERATOR_H_ */
