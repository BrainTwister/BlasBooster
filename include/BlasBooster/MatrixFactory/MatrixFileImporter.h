#ifndef MATRIXFILEIMPORTER_H_
#define MATRIXFILEIMPORTER_H_

#include "BlasBooster/MatrixFactory/MatrixFactory.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include <string>

namespace BlasBooster {

/// Import a matrix from file
class MatrixFileImporter : public MatrixFactory
{
public:

	MatrixFileImporter(filesystem::path const& file);

	virtual ~MatrixFileImporter() {}

	Matrix<Dense,double> operator()() const;

private:

	filesystem::path dataFile;

};

} // namespace BlasBooster

#endif /* MATRIXFILEIMPORTER_H_ */
