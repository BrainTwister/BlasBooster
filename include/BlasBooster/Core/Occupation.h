 #ifndef OCCUPATION_H_
#define OCCUPATION_H_

#include "BoostLib/exec_if.h"
#include "BoostLib/TypeChecker.h"
#include "TypeList.h"

namespace BlasBooster {

template <class M, class T, class P>
struct CountDesiredElementsFunctor
{
	template <class ValueChecker>
    size_t operator () (Matrix<M,T,P> const& A, ValueChecker const& valueChecker) const
    {
		typedef const Matrix<M,T,P> MatrixType;

		size_t sum(0);
		for (typename MatrixType::const_iterator iterCur(A.begin()), iterEnd(A.end());
			iterCur != iterEnd; ++iterCur)
		{
			if (valueChecker(*iterCur)) ++sum;
		}
	    return sum;
    }
};

template <class M, class P>
struct CountDesiredElementsFunctor<M,DynamicMatrix,P>
{
	template <class ValueChecker>
	size_t operator () (Matrix<M,DynamicMatrix,P> const& A, ValueChecker const& valueChecker) const
    {
		typedef const Matrix<M,DynamicMatrix,P> MatrixType;

		size_t sum(0);
		for (typename MatrixType::const_iterator iterCur(A.begin()), iterEnd(A.end());
			iterCur != iterEnd; ++iterCur)
		{
			sum += countDesiredElements(*iterCur,valueChecker);
		}
	    return sum;
    }
};

template <class M, class T, class P, class ValueChecker>
inline size_t countDesiredElements(Matrix<M,T,P> const& A, ValueChecker const& valueChecker)
{
	return CountDesiredElementsFunctor<M,T,P>()(A,valueChecker);
}

template <class ValueChecker>
struct DynamicCountDesiredElementsFunctor
{
	typedef double result_type;

	DynamicCountDesiredElementsFunctor(DynamicMatrix const& dynMatrix, ValueChecker const& valueChecker)
	 : dynMatrix_(dynMatrix), valueChecker_(valueChecker)
	{}

    template <class T>
    result_type operator () (T* = 0) const
    {
    	return boost::static_pointer_cast<T>(dynMatrix_)->getNbOfSignificantElements(valueChecker_);
    }

    DynamicMatrix dynMatrix_;
    ValueChecker const& valueChecker_;
};

template <class ValueChecker>
inline size_t countDesiredElements(DynamicMatrix const& dynMatrix, ValueChecker const& valueChecker)
{
	return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicCountDesiredElementsFunctor<ValueChecker>(dynMatrix,valueChecker));
}

} // namespace BlasBooster

#endif /* OCCUPATION_H_ */
