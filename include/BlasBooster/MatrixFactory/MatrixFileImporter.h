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

	MatrixFileImporter(size_t nbRows, size_t nbColumns, filesystem::path const& file)
     : MatrixFactory(nbRows, nbColumns), file(file)
    {}

	virtual ~MatrixFileImporter() {}

	Matrix<Dense,double> operator()() const;

private:

	filesystem::path file;

};

} // namespace BlasBooster

#endif /* MATRIXFILEIMPORTER_H_ */
