#pragma once

#include "BlasBooster/Core/BinaryFunctors.h"
#include "BlasBooster/Core/Copy.h"
#include "BlasBooster/Core/Cursor.h"
#include "BlasBooster/Core/DynamicMatrixFunctions.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MatrixBase.h"
#include "BlasBooster/Core/MatrixFileIO.h"
#include "BlasBooster/Core/MatrixFiller.h"
#include "BlasBooster/Core/MatrixMultExp.h"
#include "BlasBooster/Core/Multiplication_Native.h"
#include "BlasBooster/Core/NormPolicy.h"
#include "BlasBooster/Core/OccupationPolicy.h"
#include "BlasBooster/Core/Parameter.h"
#include "BlasBooster/Core/Storage.h"
#include "BlasBooster/Core/Transposition.h"
#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Utilities/exec_if.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/TypeChecker.h"
#include "BlasBooster/Utilities/TypeList.h"
#include "BlasBooster/Utilities/TypeName.h"
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace BlasBooster {

/**
 * \brief Column- or row major stored dense matrix.
 */
template <class T, class P>
class Matrix<Dense,T,P>
 : public MatrixBase,
   public P::dimension,
   public P::leadingDimension,
   public P::unblockedDimension,
   public Storage<T,P::onStack,P::isFixed,P::dimension::size,P::isSubMatrix>,
   public NormPolicy<Matrix<Dense,T,P>, typename P::NormType>,
   public OccupationPolicy<Matrix<Dense,T,P>>
{
public: // typedefs

    typedef Matrix<Dense,T,P> self;
    typedef Dense matrix_type;
    typedef T value_type;
    typedef const T const_value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef P parameter;
    typedef typename P::dimension dimension;
    typedef typename P::orientation orientation;
    typedef typename P::leadingDimension leadingDimension;
    typedef typename P::unblockedDimension unblockedDimension;
    typedef typename P::IndexType IndexType;
    typedef Storage<T,P::onStack,P::isFixed,P::dimension::size,P::isSubMatrix> storage;
    typedef typename storage::iterator iterator;
    typedef typename storage::const_iterator const_iterator;

public: // member functions

    /// Default constructor
    Matrix();

    /// Parameter constructor
    template <class Filler = NoFiller, class U = T>
    Matrix(IndexType nbRows, IndexType nbColumns, Filler const& filler = Filler(),
        typename std::enable_if<!std::is_same<U, DynamicMatrix>::value>::type* = 0);

    /// Parameter constructor for BlockedMatrix
    template <class U = T>
    Matrix(IndexType nbRows = 0, IndexType nbColumns = 0,
        IndexType nbUnblockedRows = 0, IndexType nbUnblockedColumns = 0,
        typename std::enable_if<std::is_same<U, DynamicMatrix>::value>::type* = 0);

    /// Parameter constructor using external memory
    Matrix(IndexType nbRows, IndexType nbColumns, T* ptrExternalMemory);

#ifndef NO_INITIALIZER_LIST_SUPPORTED
    /// Initializer list constructor
    template <class U = T>
    Matrix(std::initializer_list< std::initializer_list<T> > values,
        typename std::enable_if<!std::is_same<U, DynamicMatrix>::value>::type* = 0);

    /// Initializer constructor for BlockedMatrix
    template <class U = T>
    Matrix(std::initializer_list< std::initializer_list<T> > values,
        typename std::enable_if<std::is_same<U, DynamicMatrix>::value>::type* = 0);
#endif

    /// Submatrix constructor, use storage of reference matrix, ColumnMajor
    template <class T2, class P2, class U = P>
    Matrix(Matrix<Dense,T2,P2> const& other, IndexType nbRows, IndexType nbColumns,
        IndexType beginRow = 0, IndexType beginColumn = 0,
        typename std::enable_if<
		    std::is_same<typename P::orientation, ColumnMajor>::value and
            std::is_same<typename P2::orientation, ColumnMajor>::value and
            U::isSubMatrix
        >::type* = 0
    );

    /// Submatrix constructor, use storage of reference matrix, RowMajor
    template <class T2, class P2, class U = P>
    Matrix(Matrix<Dense,T2,P2> const& other, IndexType nbRows, IndexType nbColumns,
        IndexType beginRow = 0, IndexType beginColumn = 0,
        typename std::enable_if<
            std::is_same<typename P::orientation, RowMajor>::value and
            std::is_same<typename P2::orientation, RowMajor>::value and
            U::isSubMatrix
        >::type* = 0
    );

    /// Conversion from DenseMatrix with same orientation
    template <class T2, class P2, class ValueChecker = AbsoluteValueRangeChecker<double> >
    Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker = ValueChecker(),
        typename std::enable_if<
            std::is_same<typename P::orientation, typename P2::orientation>::value and
            !P2::isSubMatrix and !P2::isBlockedMatrix
        >::type* = 0
    );

    /// Conversion from DenseMatrix with different orientation
    template <class T2, class P2, class ValueChecker = AbsoluteValueRangeChecker<double> >
    Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker = ValueChecker(),
        typename std::enable_if<
            !std::is_same<typename P::orientation, typename P2::orientation>::value and
            !P2::isSubMatrix and !P2::isBlockedMatrix
        >::type* = 0
    );

    /// Conversion from SubDenseMatrix
    template <class T2, class P2, class ValueChecker = AbsoluteValueRangeChecker<double> >
    Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker = ValueChecker(),
        typename std::enable_if<
            std::is_same<typename P::orientation, ColumnMajor>::value and
            std::is_same<typename P2::orientation, ColumnMajor>::value and
            P2::isSubMatrix
        >::type* = 0
    );

    /// Conversion from SubDenseMatrix
    template <class T2, class P2, class ValueChecker = AbsoluteValueRangeChecker<double> >
    Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker = ValueChecker(),
        typename std::enable_if<
            std::is_same<typename P::orientation, RowMajor>::value and
            std::is_same<typename P2::orientation, RowMajor>::value and
            P2::isSubMatrix
        >::type* = 0
    );

    /// Conversion from blocked DenseMatrix
    template <class T2, class P2>
    Matrix(Matrix<Dense,T2,P2> const& other,
        typename std::enable_if<
            std::is_same<typename P::orientation, ColumnMajor>::value and
            std::is_same<typename P2::orientation, ColumnMajor>::value and
            !P::isSubMatrix and
            P2::isBlockedMatrix
        >::type* = 0
    );

    /// Conversion from DynamicMatrix
    Matrix(DynamicMatrix const& other);

    /// Conversion from SparseMatrix with same orientation
    template <class T2, class P2>
    Matrix(Matrix<Sparse,T2,P2> const& other,
        typename std::enable_if<std::is_same<typename P::orientation, typename P2::orientation>::value>::type* = 0
    );

    /// Conversion from SparseMatrix with different orientation
    template <class T2, class P2>
    Matrix(Matrix<Sparse,T2,P2> const& other,
        typename std::enable_if<!std::is_same<typename P::orientation, typename P2::orientation>::value>::type* = 0
    );

    /// Conversion from ZeroMatrix
    template <class P2>
    Matrix(Matrix<Zero,P2> const& other);

    /// Conversion from MultipleMatrix
    template <class X1, class X2>
    Matrix(MultipleMatrix<X1,X2> const& other);

    /// Construction by multiplication expression template
    template <class Op1, class Op2>
    Matrix(MatrixMultExp<Op1, Op2> const& expression);

    /// Construction by file
    Matrix(filesystem::path const& file);

    /// Default copy constructor
    Matrix(self const& other) = default;

    /// Move constructor
    Matrix(self&& other)
     : dimension(std::move(other)),
	   storage(std::forward<storage>(other))
    {
        BLASBOOSTER_DEBUG_PRINT("Matrix: Move constructor is called.");
    }

    /// Default destructor
    ~Matrix() = default;

    /// Default copy assignment operator
    Matrix& operator = (self const& other) = default;

    /// Move assignment operator
    Matrix& operator = (self&& rhs) BLASBOOSTER_NOEXCEPT {
        BLASBOOSTER_DEBUG_PRINT("Matrix: Move assignment operator is called.");
        dimension::operator=(std::forward<dimension>(rhs));
        leadingDimension::operator=(std::forward<leadingDimension>(rhs));
        unblockedDimension::operator=(std::forward<unblockedDimension>(rhs));
        storage::operator=(std::forward<storage>(rhs));
        return *this;
    }

    /// Set all elements to value
    Matrix& operator = (T value);

    //MatrixBase* clone() const { return new self(*this); }

    /// Resize function for non-blocked matrix
    template <class Filler = NoFiller, class U = T>
    void resize(IndexType nbRows, IndexType nbColumns, Filler const& filler = Filler(),
        typename std::enable_if<!std::is_same<U, DynamicMatrix>::value>::type* = 0);

    /// Resize function for BlockedMatrix
    template <class U = T>
    void resize(IndexType nbRows, IndexType nbColumns,
        IndexType nbUnblockedRows, IndexType nbUnblockedColumns,
        typename std::enable_if<std::is_same<U, DynamicMatrix>::value>::type* = 0);

    bool operator == (self const& rhs) const {
        return storage::operator==(rhs) and dimension::operator==(rhs);
    }

    template <class T2, class P2>
    bool equal(Matrix<Dense,T2,P2> const& rhs) const {
        return storage::equal(rhs)
            and this->getNbRows() == rhs.getNbRows()
            and this->getNbColumns() == rhs.getNbColumns();
    }

    template <class T2, class P2>
    bool notEqual(Matrix<Dense,T2,P2> const& rhs) const {
        return !equal(rhs);
    }

    T& operator () (IndexType row, IndexType column);
    const T& operator () (IndexType row, IndexType column) const;

    // TODO: move to dimension
    template <class U = P>
    IndexType getLdColumns(typename std::enable_if<!U::isSubMatrix>::type* = 0) const {
        return this->getNbColumns();
    }

    template <class U = P>
    IndexType getLdColumns(typename std::enable_if<U::isSubMatrix>::type* = 0) const {
        return leadingDimension::getLdColumns();
    }

    template <class U = P>
    IndexType getLdRows(typename std::enable_if<!U::isSubMatrix>::type* = 0) const {
        return this->getNbRows();
    }

    template <class U = P>
    IndexType getLdRows(typename std::enable_if<U::isSubMatrix>::type* = 0) const {
        return leadingDimension::getLdRows();
    }

    const std::type_info& getTypeInfo() const { return typeid(*this); }

    size_t getTypeIndex() const { return typeIndex_; }

    friend void swap( self& a, self& b ) BLASBOOSTER_NOEXCEPT {
        using std::swap; // bring in swap for built-in types
        swap(a.data_,b.data_);
        swap(a.size_,b.size_);
        swap(a.ownMemory_,b.ownMemory_);
        swap(a.nbRows_,b.nbRows_);
        swap(a.nbColumns_,b.nbColumns_);
        //swap(a.storage,b.storage);
    }

    static const size_t typeIndex_ = GetIndex<self, DynamicMatrixTypeList>::value;

    static const std::string name() { return "Matrix<Dense," + TypeName<T>::value() + ">"; }

private:

    template <class M2, class T2, class P2>
    friend struct Matrix;

    template <class M1, class T1, class P1, class M2, class T2, class P2, class M3, class T3, class P3, class Interface>
    friend struct MultiplicationFunctor;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<dimension>(*this);
        ar & boost::serialization::base_object<storage>(*this);
    }

    void checkIfPositionIsAvailable(IndexType row, typename P::IndexType column) const;

    template <class U = P>
    size_t getPosition(IndexType row, typename P::IndexType column,
        typename std::enable_if<std::is_same<typename U::orientation, RowMajor>::value>::type* = 0) const;

    template <class U = P>
    size_t getPosition(IndexType row, typename P::IndexType column,
        typename std::enable_if<std::is_same<typename U::orientation, ColumnMajor>::value>::type* = 0) const;

}; // class DenseMatrix

template <class T, class P>
Matrix<Dense,T,P>::Matrix()
 : dimension(), storage()
{}

template <class T, class P>
template <class Filler, class U>
Matrix<Dense,T,P>::Matrix(typename P::IndexType nbRows, typename P::IndexType nbColumns, Filler const& filler,
    typename std::enable_if<!std::is_same<U, DynamicMatrix>::value>::type*)
 : dimension(nbRows,nbColumns),
   storage(nbRows*nbColumns)
{
    filler(*this);
}

template <class T, class P>
template <class U>
Matrix<Dense,T,P>::Matrix(typename P::IndexType nbRows, typename P::IndexType nbColumns,
    typename P::IndexType nbUnblockedRows, typename P::IndexType nbUnblockedColumns,
    typename std::enable_if<std::is_same<U, DynamicMatrix>::value>::type*)
 : dimension(nbRows,nbColumns),
   unblockedDimension(nbUnblockedRows,nbUnblockedColumns),
   storage(nbRows*nbColumns)
{}

template <class T, class P>
Matrix<Dense,T,P>::Matrix(typename P::IndexType nbRows, typename P::IndexType nbColumns,
    T* ptrExternalMemory)
 : dimension(nbRows,nbColumns),
   storage(ptrExternalMemory,nbRows*nbColumns)
{}

#ifndef NO_INITIALIZER_LIST_SUPPORTED
template <class T, class P>
template <class U>
Matrix<Dense,T,P>::Matrix(std::initializer_list< std::initializer_list<T> > values,
    typename std::enable_if<!std::is_same<U, DynamicMatrix>::value>::type*)
 : dimension(values.size(),values.begin()->size()),
   storage(values.size() * values.begin()->size())
{
    typedef Cursor<Matrix<Dense,T,P>, Direction::Row> RowCursor;
    typedef Cursor<RowCursor, Direction::Column> ColumnCursor;

    auto val1 = values.begin();
    for (RowCursor rowCur(*this,0), rowEnd(*this,this->getNbRows()); rowCur != rowEnd; ++rowCur, ++val1 )
    {
        auto val2 = val1->begin();
        for ( ColumnCursor columnCur(*this,rowCur.begin()),
            columnEnd(*this,rowCur.end()); columnCur != columnEnd; ++columnCur, ++val2 )
        {
            *columnCur = *val2;
        }
    }
}

template <class T, class P>
template <class U>
Matrix<Dense,T,P>::Matrix(std::initializer_list< std::initializer_list<T> > values,
    typename std::enable_if<std::is_same<U, DynamicMatrix>::value>::type*)
 : dimension(values.size(),values.begin()->size()),
   storage(values.size() * values.begin()->size())
{
    typedef Cursor<Matrix<Dense,T,P>, Direction::Row> RowCursor;
    typedef Cursor<RowCursor, Direction::Column> ColumnCursor;

    auto val1 = values.begin();
    typename P::IndexType ubRowsTmp, ubColumnsTmp;
    for (RowCursor rowCur(*this,0), rowEnd(*this,this->getNbRows()); rowCur != rowEnd; ++rowCur, ++val1)
    {
        auto val2 = val1->begin();
        ubRowsTmp = getNbRows(*val2);
        this->ubRows_ += ubRowsTmp;
        ubColumnsTmp = 0;
        for (ColumnCursor columnCur(*this,rowCur.begin()),
            columnEnd(*this,rowCur.end()); columnCur != columnEnd; ++columnCur, ++val2)
        {
            *columnCur = *val2;
            if (ubRowsTmp != getNbRows(*val2)) throw std::runtime_error("wrong sub-dimension");
            ubColumnsTmp += getNbColumns(*val2);
        }
        this->ubColumns_ = ubColumnsTmp;
    }
}
#endif

// Submatrix constructor, use storage of reference matrix, ColumnMajor
template <class T, class P>
template <class T2, class P2, class U>
Matrix<Dense,T,P>::Matrix(Matrix<Dense,T2,P2> const& other, typename P::IndexType nbRows,
    typename P::IndexType nbColumns, typename P::IndexType beginRow, typename P::IndexType beginColumn,
    typename std::enable_if<
        std::is_same<typename P::orientation, ColumnMajor>::value and
        std::is_same<typename P2::orientation, ColumnMajor>::value and
        U::isSubMatrix
    >::type*)
 : dimension(nbRows,nbColumns),
   leadingDimension(other.getNbRows(),other.getNbColumns()),
   // TODO: avoid const_cast
   storage(const_cast<T2*>(other.getDataPointer() + beginRow + beginColumn * other.getNbRows()),
       nbRows, nbColumns, other.getNbRows() - nbRows)
{}

template <class T, class P>
template <class T2, class P2, class U>
Matrix<Dense,T,P>::Matrix(Matrix<Dense,T2,P2> const& other, typename P::IndexType nbRows,
    typename P::IndexType nbColumns, typename P::IndexType beginRow, typename P::IndexType beginColumn,
    typename std::enable_if<
        std::is_same<typename P::orientation, RowMajor>::value and
        std::is_same<typename P2::orientation, RowMajor>::value and
        U::isSubMatrix
    >::type*)
 : dimension(nbRows,nbColumns),
   leadingDimension(other.getNbRows(),other.getNbColumns()),
   storage(
       const_cast<T2*>(other.getDataPointer()) + beginRow * other.getNbColumns() + beginColumn,
       other.getSize() - beginRow * other.getNbColumns() - beginColumn
   )
{}

// Conversion from DenseMatrix with same orientation
template <class T, class P>
template <class T2, class P2, class ValueChecker>
Matrix<Dense,T,P>::Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker,
    typename std::enable_if<
        std::is_same<typename P::orientation, typename P2::orientation>::value and
        !P2::isSubMatrix and !P2::isBlockedMatrix
    >::type*)
  : dimension(other.getNbRows(), other.getNbColumns()),
    storage(other)
{}

// Conversion from DenseMatrix with different orientation
template <class T, class P>
template <class T2, class P2, class ValueChecker>
Matrix<Dense,T,P>::Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker,
    typename std::enable_if<
        !std::is_same<typename P::orientation, typename P2::orientation>::value and
        !P2::isSubMatrix and !P2::isBlockedMatrix
    >::type*)
  : dimension(other.getNbRows(), other.getNbColumns()),
    storage(transpose(other))
{}

template <class T, class P>
template <class T2, class P2, class ValueChecker>
Matrix<Dense,T,P>::Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker,
    typename std::enable_if<
        std::is_same<typename P::orientation, ColumnMajor>::value and
        std::is_same<typename P2::orientation, ColumnMajor>::value and
        P2::isSubMatrix
    >::type*)
  : dimension(other.getNbRows(),other.getNbColumns()),
    storage(other.getSize())
{
    typename storage::iterator iterCur(this->begin());
    typename Matrix<Dense,T2,P2>::const_iterator otherIterCur(other.begin()), otherIterEnd(other.end());

    for ( ; otherIterCur != otherIterEnd; ++otherIterCur, ++iterCur) {
        *iterCur = valueChecker(*otherIterCur) ? *otherIterCur : 0.0;
    }
}

/// Conversion from SubDenseMatrix
template <class T, class P>
template <class T2, class P2, class ValueChecker>
Matrix<Dense,T,P>::Matrix(Matrix<Dense,T2,P2> const& other, ValueChecker const& valueChecker,
    typename std::enable_if<
        std::is_same<typename P::orientation, RowMajor>::value and
        std::is_same<typename P2::orientation, RowMajor>::value and
        P2::isSubMatrix
    >::type*)
  : dimension(other.getNbRows(),other.getNbColumns()),
    storage(other.getSize())
{
    typename storage::iterator iterCur(this->begin());
    typename Matrix<Dense,T2,P2>::const_iterator otherIterCur(other.begin());

    typename P2::IndexType leadingDifference(other.getLdColumns() - other.getNbColumns());

    for ( size_t rowCur(0), rowEnd(other.getNbRows()); rowCur != rowEnd; ++rowCur ) {
        for ( size_t columnCur(0), columnEnd(other.getNbColumns()); columnCur != columnEnd; ++columnCur ) {
            *iterCur++ = *otherIterCur++;
        }
        otherIterCur += leadingDifference;
    }
}

/// Conversion from SubDenseMatrix
template <class T, class P>
template <class T2, class P2>
Matrix<Dense,T,P>::Matrix(Matrix<Dense,T2,P2> const& other,
    typename std::enable_if<
        std::is_same<typename P::orientation, ColumnMajor>::value and
        std::is_same<typename P2::orientation, ColumnMajor>::value and
        !P::isSubMatrix and
        P2::isBlockedMatrix
    >::type*
) : dimension(other.getUnblockedRows(), other.getUnblockedColumns()),
    storage(other.getUnblockedRows() * other.getUnblockedColumns())
{
    typename P::IndexType subRowOffset(0), subRowOffsetTmp(0), subColumnOffset(0);

    typedef Cursor<const Matrix<Dense,T2,P2>, Direction::Row> RowCursor;
    typedef Cursor<RowCursor, Direction::Column> ColumnCursor;
    for (RowCursor rowCur(other,0), rowEnd(other,other.getNbRows()); rowCur != rowEnd; ++rowCur)
    {
        for (ColumnCursor columnCur(other,rowCur.begin()),
            columnEnd(other,rowCur.end()); columnCur != columnEnd; ++columnCur)
        {
            typedef Matrix<Dense, T, Parameter<typename P::IndexType, typename P::orientation, typename P::SizeType, LeadingDimension>> SubMatrix;

            SubMatrix subMatrixOut(*this,getNbRows(*columnCur),getNbColumns(*columnCur),subRowOffset,subColumnOffset);

            self subMatrixIn(*columnCur);
            copy(subMatrixIn,subMatrixOut);

            // TODO: rowOffset is ideally determined one time (all submatrices in a column have the same row size).
            // But I don't know yet how to determine the offset in the outer loop.
            subRowOffsetTmp = getNbRows(*columnCur);
            subColumnOffset += getNbColumns(*columnCur);
        }
        subRowOffset += subRowOffsetTmp;
        subColumnOffset = 0;
    }
}

template <class M>
struct ConvertToDenseMatrix
{
    typedef M result_type;

    ConvertToDenseMatrix(DynamicMatrix const& dynMatrix)
     : dynMatrix_(dynMatrix)
    {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        M matrix(*std::static_pointer_cast<T>(dynMatrix_));
        return matrix;
    }

    DynamicMatrix dynMatrix_;
};

template <class T, class P>
Matrix<Dense,T,P>::Matrix(DynamicMatrix const& dynMatrix)
 : dimension(), storage()
{
    self matrix = exec_if<DynamicMatrixTypeList>(TypeChecker(dynMatrix->getTypeIndex()),
        ConvertToDenseMatrix<self>(dynMatrix));
    swap(*this,matrix);
}

// Conversion from SparseMatrix with same orientation
template <class T, class P>
template <class T2, class P2>
Matrix<Dense,T,P>::Matrix(Matrix<Sparse,T2,P2> const& other,
    typename std::enable_if<std::is_same<typename P::orientation, typename P2::orientation>::value>::type*)
 : dimension(other.getNbRows(), other.getNbColumns()), storage(other.getSize())
{
    typedef typename Matrix<Sparse,T2,P2>::const_index_iterator ConstIndexIterator;
    typedef typename Matrix<Sparse,T2,P2>::const_iterator ConstIterator;

    this->fill(0);

    iterator iterDense = this->begin();
    for (ConstIndexIterator iterOffsetCur(other.beginOffset()),
        iterOffsetEnd(other.endOffset() - 1); iterOffsetCur != iterOffsetEnd; ++iterOffsetCur)
    {
    	ConstIterator iterValueCur(other.begin() + *iterOffsetCur);
        for (ConstIndexIterator iterKeyCur(other.beginKey() + *iterOffsetCur),
            iterKeyEnd(other.beginKey() + *(iterOffsetCur + 1)); iterKeyCur != iterKeyEnd; ++iterKeyCur, ++iterValueCur)
        {
        	iterDense[*iterKeyCur] = *iterValueCur;
        }
        iterDense += this->getMajorDimension();
    }
}

// Conversion from SparseMatrix with different orientation
template <class T, class P>
template <class T2, class P2>
Matrix<Dense,T,P>::Matrix(Matrix<Sparse,T2,P2> const& other,
    typename std::enable_if<!std::is_same<typename P::orientation, typename P2::orientation>::value>::type*)
 : dimension(other.getNbRows(), other.getNbColumns()), storage(other.getSize())
{
    typedef typename Matrix<Sparse,T2,P2>::const_index_iterator ConstIndexIterator;
    typedef typename Matrix<Sparse,T2,P2>::const_iterator ConstIterator;

    this->fill(0);

    iterator iterDense = this->begin();
    for (ConstIndexIterator iterOffsetCur(other.beginOffset()),
        iterOffsetEnd(other.endOffset() - 1); iterOffsetCur != iterOffsetEnd; ++iterOffsetCur)
    {
    	ConstIterator iterValueCur(other.begin() + *iterOffsetCur);
        for (ConstIndexIterator iterKeyCur(other.beginKey() + *iterOffsetCur),
            iterKeyEnd(other.beginKey() + *(iterOffsetCur + 1)); iterKeyCur != iterKeyEnd; ++iterKeyCur, ++iterValueCur)
        {
        	iterDense[*iterKeyCur * this->getMajorDimension()] = *iterValueCur;
        }
        ++iterDense;
    }
}

// Conversion from ZeroMatrix
template <class T, class P>
template <class P2>
Matrix<Dense,T,P>::Matrix(Matrix<Zero,P2> const& other)
 : dimension(other.getNbRows(), other.getNbColumns()), storage(other.getNbRows() * other.getNbColumns())
{
   AllFiller<T>(0.0)(*this);
}

// Conversion from MultipleMatrix
template <class T, class P>
template <class X1, class X2>
Matrix<Dense,T,P>::Matrix(MultipleMatrix<X1,X2> const& other)
 : dimension(other.getNbRows(), other.getNbColumns()), storage(other.getSize())
{
    *this = other.getMatrix1();
    *this += other.getMatrix2();
}

// Construction by multiplication expression template
template <class T, class P>
template <class Op1, class Op2>
Matrix<Dense,T,P>::Matrix(MatrixMultExp<Op1, Op2> const& expression)
{
	*this = expression.template execute<Native>();
}

// Construction by file
template <class T, class P>
Matrix<Dense,T,P>::Matrix(filesystem::path const& file)
{
	std::ifstream ifs(file.string());
	if (!ifs) throw BlasBoosterException("Can't open file " + file.string());
	ifs >> *this;
}

template <class T, class P>
Matrix<Dense,T,P>& Matrix<Dense,T,P>::operator = (T value)
{
    for (iterator iterCur(this->begin()), iterEnd(this->end()); iterCur != iterEnd; ++iterCur)
    {
        *iterCur = value;
    }
    return *this;
}

template <class T, class P>
template <class Filler, class U>
void Matrix<Dense,T,P>::resize(typename P::IndexType nbRows, typename P::IndexType nbColumns, Filler const& filler,
    typename std::enable_if<!std::is_same<U, DynamicMatrix>::value>::type*)
{
    this->nbRows_ = nbRows;
    this->nbColumns_ = nbColumns;
    static_cast<storage*>(this)->resize(nbRows*nbColumns);
    filler(*this);
}

template <class T, class P>
template <class U>
void Matrix<Dense,T,P>::resize(typename P::IndexType nbRows, typename P::IndexType nbColumns,
    typename P::IndexType nbUnblockedRows, typename P::IndexType nbUnblockedColumns,
    typename std::enable_if<std::is_same<U, DynamicMatrix>::value>::type*)
{
    this->nbRows_ = nbRows;
    this->nbColumns_ = nbColumns;
    this->ubRows_ = nbUnblockedRows;
    this->ubColumns_ = nbUnblockedColumns;
    static_cast<storage*>(this)->resize(nbRows*nbColumns);
}

template <class T, class P>
T& Matrix<Dense,T,P>::operator () (typename P::IndexType row, typename P::IndexType column)
{
    return this->getDataPointer()[getPosition(row,column)];
}

template <class T, class P>
const T& Matrix<Dense,T,P>::operator () (typename P::IndexType row, typename P::IndexType column) const
{
    return this->getDataPointer()[getPosition(row,column)];
}

template <class T, class P>
void Matrix<Dense,T,P>::checkIfPositionIsAvailable(typename P::IndexType row, typename P::IndexType column) const
{
    if ( row >= this->getNbRows() ) throw std::runtime_error("row > getNbRows()");
    if ( column >= this->getNbColumns() ) throw std::runtime_error("column > getNbColumn()");
}

template <class T, class P>
template <class U>
size_t Matrix<Dense,T,P>::getPosition(typename P::IndexType row, typename P::IndexType column,
    typename std::enable_if<std::is_same<typename U::orientation, ColumnMajor>::value>::type*) const
{
    #ifdef BLASBOOSTER_DEBUG_MODE
        checkIfPositionIsAvailable(row,column);
    #endif
    return row + column * this->getNbRows();
}

template <class T, class P>
template <class U>
size_t Matrix<Dense,T,P>::getPosition(typename P::IndexType row, typename P::IndexType column,
    typename std::enable_if<std::is_same<typename U::orientation, RowMajor>::value>::type*) const
{
    #ifdef BLASBOOSTER_DEBUG_MODE
        checkIfPositionIsAvailable(row,column);
    #endif
    return row * this->getNbColumns() + column;
}

template <class T, class P>
void createHilbert(Matrix<Dense,T,P>& matrix, typename std::enable_if<std::is_arithmetic<T>::value>::type* dummy = 0)
{
    T one(1), row(1), column(1);

    typedef Cursor<Matrix<Dense,T,P>, Direction::Row> RowCursor;
    typedef Cursor<RowCursor, Direction::Column> ColumnCursor;
    for (RowCursor rowCur(matrix,0), rowEnd(matrix,matrix.getNbRows());
        rowCur != rowEnd; ++rowCur, row += one)
    {
        column = 1.0e0;
        for (ColumnCursor columnCur(matrix,rowCur.begin()), columnEnd(matrix,rowCur.end());
            columnCur != columnEnd; ++columnCur, column += one)
        {
            *columnCur = one / (row + column - one);
        }
    }
}

template <class T, class P>
void createNumbered(Matrix<Dense,T,P>& matrix, typename std::enable_if<std::is_arithmetic<T>::value>::type* dummy = 0)
{
    T number(1);
    for (typename Matrix<Dense,T,P>::iterator iterCur(matrix.begin()), iterEnd(matrix.end());
        iterCur != iterEnd; ++iterCur, ++number)
    {
        *iterCur = number;
    }
}

} // namespace BlasBooster
