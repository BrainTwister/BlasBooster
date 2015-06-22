#ifndef MULTIPLICATIONDETAILS_H_
#define MULTIPLICATIONDETAILS_H_

namespace BlasBooster {

struct InitializeMultiplicationResult
{
    typedef void result_type;

    InitializeMultiplicationResult(DynamicMatrix const& ptrA, DynamicMatrix const& ptrB, DynamicMatrix& ptrC)
     : ptrA_(ptrA), ptrB_(ptrB), ptrC_(ptrC)
    {}

    template <class T1, class T2>
    result_type operator () (T1* = 0, T2* = 0) const
    {
        typedef typename MultiplicationResult<T1,T2>::type ResultType;
        if (isMorePrecise<ResultType>(ptrC_)) {
            ptrC_ = DynamicMatrix(new ResultType(
                boost::static_pointer_cast<T1>(ptrA_)->getNbRows(),
                boost::static_pointer_cast<T2>(ptrB_)->getNbColumns()
            ));
        }
    }

    DynamicMatrix ptrA_;
    DynamicMatrix ptrB_;
    DynamicMatrix& ptrC_;
};

template < class IntegerTypeA, class IntegerTypeB, class TypeC >
inline void initialize( TypeC& ptrC, IntegerTypeA aCur, const IntegerTypeA& aEnd, IntegerTypeB bCur,
    typename boost::enable_if< boost::mpl::and_<
        boost::is_same<typename IntegerTypeA::collection::value_type, DynamicMatrix>,
        boost::is_same<typename IntegerTypeB::collection::value_type, DynamicMatrix>,
        boost::is_same<TypeC, DynamicMatrix>
    > >::type* dummy = 0 )
{
    for ( ; aCur != aEnd; ++aCur, ++bCur ) {
        exec_if_2dim<TypeList>(Checker((*aCur)->getTypeIndex()), Checker((*bCur)->getTypeIndex()),
            InitializeMultiplicationResult(*aCur,*bCur,ptrC));
    }
    setToZero(ptrC);
}

template < class IntegerTypeA, class IntegerTypeB, class TypeC >
inline void initialize( TypeC& c, IntegerTypeA& /*aCur*/, IntegerTypeA& /*aEnd*/, IntegerTypeB& /*bCur*/,
    typename boost::enable_if< boost::mpl::and_<
        boost::is_arithmetic<typename IntegerTypeA::collection::value_type>,
        boost::is_arithmetic<typename IntegerTypeB::collection::value_type>,
        boost::is_arithmetic<TypeC>
    > >::type* dummy = 0 )
{
    c = 0;
}

} // namespace BlasBooster

#endif /* MULTIPLICATIONDETAILS_H_ */
