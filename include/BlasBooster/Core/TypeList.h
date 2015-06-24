#ifndef TYPELIST_H_
#define TYPELIST_H_

#include "Matrix.h"
#include <boost/mpl/vector.hpp>

namespace BlasBooster {

template <class T1, class T2>
struct MultipleMatrix;

/**
 * \brief Possible matrix types for DynamicMatrix.
 *
 * Attention! Only listed types can be used as DynamicMatrix!
 *
 * The list order is important for the MatrixConverter.
 * The first matrix type in which a sub-matrix can be converted will be taken.
 *
 * TODO: change into DynamicMatrixTypeList
 *
 */
typedef boost::mpl::vector<
    //Matrix<Zero,NoType>,
    Matrix<Sparse,float>,
    Matrix<Dense,float>,
    Matrix<Sparse,double>,
    MultipleMatrix< Matrix<Sparse,double>,Matrix<Sparse,float> >,
    MultipleMatrix< Matrix<Sparse,double>,Matrix<Dense,float> >,
    Matrix<Dense,double>
> TypeList;

} // namespace BlasBooster

#endif /* TYPELIST_H_ */

