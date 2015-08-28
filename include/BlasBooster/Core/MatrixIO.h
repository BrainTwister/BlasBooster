// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MATRIXIO_H_
#define MATRIXIO_H_

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Utilities/exec_if.h"
#include "BlasBooster/Utilities/TypeChecker.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include <iostream>
#include "../Utilities/TypeList.h"

namespace BlasBooster {

/// Matrix print manipulator for full information
static int const matrixPrintIndex = std::ios_base::xalloc();

inline std::ostream& fullprint(std::ostream& stream)
{
    stream.iword(matrixPrintIndex) = 1;
    return stream;
}

/// Default matrix print manipulator
inline std::ostream& shortprint(std::ostream& stream)
{
    stream.iword(matrixPrintIndex) = 0;
    return stream;
}

template <class M, class T, class P>
struct MatrixPrintFunctor
{
    void operator () (std::ostream& stream, Matrix<M,T,P> const& A) const
    {
        static_assert(wrong_t<M>::value, "Primary template must not be instantiated.");
    }
};

template <class T, class P>
struct MatrixPrintFunctor<Dense,T,P>
{
    void operator () (std::ostream& stream, Matrix<Dense,T,P> const& A) const
    {
        const size_t maxNbRowsForPrinting = 100;
        const size_t maxNbColumnsForPrinting = 100;

        if ((A.getNbRows() > maxNbRowsForPrinting) or
            (A.getNbColumns() > maxNbColumnsForPrinting))
        {
            stream << "Matrix too large for printing." << std::endl;
        }
        else
        {
            if (stream.iword(matrixPrintIndex) == 1) {
                stream << A.name() << std::endl
                       << "Dimension = " << A.getNbRows() << " x " << A.getNbColumns() << std::endl;
            }
            std::vector<size_t> width(A.getNbColumns());
            std::vector<size_t>::iterator widthCur(width.begin()), widthEnd(width.end());
            for ( ; widthCur != widthEnd; ++widthCur ) *widthCur = 0;

            typedef Cursor<const Matrix<Dense,T,P>, Direction::Row> RowCursor;
            typedef Cursor<RowCursor, Direction::Column> ColumnCursor;
            for ( RowCursor rowCur(A,0), rowEnd(A,A.getNbRows()); rowCur != rowEnd; ++rowCur )
            {
                widthCur = width.begin();
                for ( ColumnCursor columnCur(A,rowCur.begin()),
                    columnEnd(A,rowCur.end()); columnCur != columnEnd; ++columnCur, ++widthCur )
                {
                    std::stringstream element;
                    element << std::scientific << std::setprecision(10) << *columnCur;
                    *widthCur = std::max(*widthCur,element.str().size());
                }
            }

            for ( widthCur = width.begin(); widthCur != widthEnd; ++widthCur ) ++(*widthCur);

            stream << std::scientific << std::setprecision(10) << std::endl;

            for ( RowCursor rowCur(A,0), rowEnd(A,A.getNbRows()); rowCur != rowEnd; ++rowCur )
            {
                widthCur = width.begin();
                for ( ColumnCursor columnCur(A,rowCur.begin()),
                    columnEnd(A,rowCur.end()); columnCur != columnEnd; ++columnCur, ++widthCur )
                {
                    stream << std::setw(*widthCur) << *columnCur << std::flush;
                }
                stream << std::endl;
            }
            stream << std::endl;
        }
    }
};

template <class T, class P>
struct MatrixPrintFunctor<Sparse,T,P>
{
    void operator () (std::ostream& stream, Matrix<Sparse,T,P> const& A) const
    {
        typedef const Matrix<Sparse,T,P> ConstMatrix;

        const size_t maxSizeForPrinting = 100;

        if (A.getSize() > maxSizeForPrinting) {
            stream << "SparseMatrix (Size = " << A.getSize() << ") too large for printing." << std::endl;
        } else {
            stream << A.name() << std::endl
                   << "Size = " << A.getSize() << std::endl
                   << "Dimension = " << A.getNbRows() << " x " << A.getNbColumns() << std::endl;

            stream << "Value array = ";
            for (typename ConstMatrix::const_iterator iterCur(A.begin()), iterEnd(A.end());
                iterCur != iterEnd; ++iterCur)
            {
                stream << *iterCur << " ";
            }
            stream << std::endl;

            stream << "Key array = ";
            for (typename ConstMatrix::const_index_iterator iterCur(A.beginKey()), iterEnd(A.endKey());
                iterCur != iterEnd; ++iterCur)
            {
                stream << *iterCur << " ";
            }
            stream << std::endl;

            stream << "Offset array = ";
            for (typename ConstMatrix::const_index_iterator iterCur(A.beginOffset()), iterEnd(A.endOffset());
                iterCur != iterEnd; ++iterCur)
            {
                stream << *iterCur << " ";
            }
        }
    }
};

template <class M, class T, class P>
std::ostream& operator << (std::ostream& stream, Matrix<M,T,P> const& A)
{
    MatrixPrintFunctor<M,T,P>()(stream,A);
    return stream << std::flush;
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& stream, MultipleMatrix<T1,T2> const& A)
{
    return stream << A.getMatrix1() << A.getMatrix2() << std::flush;
}

struct DynamicMatrixPrintFunctor
{
    typedef void result_type;

    DynamicMatrixPrintFunctor(std::ostream& stream, DynamicMatrix const& dynMatrix)
     : dynMatrix_(dynMatrix), ptrStream_(&stream)
    {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        *ptrStream_ << *(std::static_pointer_cast<T>(dynMatrix_));
    }

    DynamicMatrix dynMatrix_;
    std::ostream* ptrStream_;
};

inline std::ostream& operator << (std::ostream& stream, DynamicMatrix const& dynMatrix)
{
    if (dynMatrix.get() == 0) {
        stream << "No Matrix found.";
    } else {
        exec_if<DynamicMatrixTypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicMatrixPrintFunctor(stream,dynMatrix));
    }
    return stream << std::flush;
}

} // namespace BlasBooster

#endif /* MATRIXIO_H_ */
