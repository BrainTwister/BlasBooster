// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MULTIPLEMATRIX_H_
#define MULTIPLEMATRIX_H_

#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/MatrixBase.h"
#include "BlasBooster/Core/TypeList.h"
#include "BlasBooster/Utilities/TypeName.h"
#include "BlasBooster/Utilities/TypeRegister.h"

namespace BlasBooster {

/**
 * @brief Handle two matrix types as one matrix.
 *
 * The design is like an expression template for the addition of two matrices.
 * Instead of references, pointers are used because in the case of the conversion
 * from a matrix the internal matrices of MultipleMatrix have to be constructed.
 *
 * TODO: Use variadic template to use more than two matrices
 */
template <class T1, class T2>
struct MultipleMatrix
 : public MatrixBase
{
    explicit MultipleMatrix(std::shared_ptr<T1> const& ptrT1 = std::shared_ptr<T1>(),
    	std::shared_ptr<T2> const& ptrT2 = std::shared_ptr<T2>()
    )
	 : ptrT1_(ptrT1), ptrT2_(ptrT2)
	{
    	if (ptrT1_ and ptrT2_)
    	{
		    if (ptrT1_->getNbRows() != ptrT2_->getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
		    if (ptrT1_->getNbColumns() != ptrT2_->getNbColumns()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
	    }
	}

//	template <class M, class T, class P>
//	MultipleMatrix(Matrix<M,T,P> const& m)
//	 : ptrT1(nullptr), ptrT2(nullptr)
//	{}

    void reset(std::shared_ptr<T1> const& ptrT1 = std::shared_ptr<T1>(),
    	std::shared_ptr<T2> const& ptrT2 = std::shared_ptr<T2>()
    ){
    	ptrT1_ = ptrT1;
    	ptrT2_ = ptrT2;

    	if (ptrT1_ and ptrT2_)
    	{
		    if (ptrT1_->getNbRows() != ptrT2_->getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
		    if (ptrT1_->getNbColumns() != ptrT2_->getNbColumns()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
	    }
	}

	typename T1::IndexType getNbRows() const { return ptrT1_->getNbRows(); }
	typename T1::IndexType getNbColumns() const { return ptrT1_->getNbColumns(); }
	typename T1::IndexType getSize() const { return ptrT1_->getSize(); }

	T1& getMatrix1() const { return *ptrT1_; }
	T2& getMatrix2() const { return *ptrT2_; }

	size_t getNbOfSignificantElements(double threshold = 0.0) const {
		return ptrT1_->getNbOfSignificantElements(threshold) + ptrT2_->getNbOfSignificantElements(threshold);
	}

	double getOccupation(double threshold = 0.0) const
	{
		// TODO
		BLASBOOSTER_CORE_FAILURE("not implemented yet");
	}

	bool isOccupationLargerThan(double value, double threshold = 0.0) const
	{
		// TODO
		BLASBOOSTER_CORE_FAILURE("not implemented yet");
	}

	double getNorm() const
	{
		// TODO
		BLASBOOSTER_CORE_FAILURE("not implemented yet");
	}

	bool isNormLargerThan(double value) const
	{
		// TODO
		BLASBOOSTER_CORE_FAILURE("not implemented yet");
	}

    const std::type_info& getTypeInfo() const { return typeid(*this); }

    size_t getTypeIndex() const { return typeIndex_; }

    static const size_t typeIndex_ = TypeRegister<TypeList>::getTypeIndex<MultipleMatrix>::value;

private:

    std::shared_ptr<T1> ptrT1_;
    std::shared_ptr<T2> ptrT2_;

};

template <class T1, class T2> struct TypeName<MultipleMatrix<T1,T2> >
{
	static const std::string value() { return "MultipleMatrix"; }
};

} // namespace BlasBooster

#endif // MULTIPLEMATRIX_H_
