#pragma once

#include <boost/mpl/bool.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/assert.hpp>

using namespace boost::mpl;

template <
    class Executor,
    class BaseLHS,
    class DerivedListLHS,
    class BaseRHS = BaseLHS,
    class DerivedListRHS = DerivedListLHS,
    typename ResultType = void
>
class StaticDispatcher
{
    typedef typename front<DerivedListLHS>::type Head;
    typedef typename pop_front<DerivedListLHS>::type Tail;

public:

    static ResultType Go( BaseLHS& lhs, BaseRHS& rhs, Executor exec )
    {
        if ( Head* p1 = dynamic_cast<Head*>(&lhs) )
        {
            return StaticDispatcher<Executor,BaseLHS,DerivedListLHS,BaseRHS,DerivedListRHS,ResultType>::DispatchRHS(*p1,rhs,exec);
        }

        BOOST_MPL_ASSERT_NOT(( boost::mpl::empty<Tail> ));

        return StaticDispatcher<Executor,BaseLHS,Tail,BaseRHS,DerivedListRHS,ResultType>::Go(lhs,rhs,exec);
    }

    template <class SomeLHS>
    static ResultType DispatchRHS( SomeLHS& lhs, BaseRHS& rhs, Executor exec )
    {
        typedef typename front<DerivedListRHS>::type Head;
        typedef typename pop_front<DerivedListRHS>::type Tail;

        if ( Head* p2 = dynamic_cast<Head*>(&rhs) )
        {
            return exec.Mult(lhs,*p2);
        }

        BOOST_MPL_ASSERT_NOT(( boost::mpl::empty<Tail> ));

        return StaticDispatcher<Executor,SomeLHS,DerivedListLHS,BaseRHS,Tail,ResultType>::DispatchRHS(lhs,rhs,exec);

    }
};
