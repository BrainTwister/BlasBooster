#ifndef EXEC_IF_2DIM_H_
#define EXEC_IF_2DIM_H_

#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <stdexcept>

namespace BlasBooster {

template< bool done = true >
struct exec_if_1dim_impl
{
    template< class T1, class Iterator, class LastIterator, class Pred, class Exec >
    static typename Exec::result_type execute( T1*, Iterator*, LastIterator*, const Pred&, const Exec& )
    {
    	throw std::runtime_error("exec_if_1dim: type not found.");
    }
};

template<>
struct exec_if_1dim_impl<false>
{
    template< class T1, class Iterator, class LastIterator, class Pred, class Exec >
    static typename Exec::result_type execute( T1*, Iterator*, LastIterator*, const Pred& p, const Exec& e )
    {
	    typedef typename boost::mpl::deref<Iterator>::type T2;

	    if (!p(static_cast<T2*>(0)))
	    {
	        typedef typename boost::mpl::next<Iterator>::type iter;
	        return exec_if_1dim_impl<boost::is_same<iter, LastIterator>::value>
		        ::execute(static_cast<T1*>(0), static_cast<iter*>(0), static_cast<LastIterator*>(0), p, e);
	    }
	    else
	        return e(static_cast<T1*>(0), static_cast<T2*>(0));
    }
};

template< bool done = true >
struct exec_if_2dim_impl
{
    template< class Sequence, class Iterator, class LastIterator, class Pred1, class Pred2, class Exec >
    static typename Exec::result_type execute( Sequence*, Iterator*, LastIterator*, const Pred1& p1, const Pred2& p2, const Exec& )
    {
    	throw std::runtime_error("exec_if_2dim: type not found.");
    }
};

template<>
struct exec_if_2dim_impl<false>
{
    template< class Sequence, class Iterator, class LastIterator, class Pred1, class Pred2, class Exec >
    static typename Exec::result_type execute( Sequence*, Iterator*, LastIterator*, const Pred1& p1, const Pred2& p2, const Exec& e )
    {
	    typedef typename boost::mpl::deref<Iterator>::type T1;

	    if (!p1(static_cast<T1*>(0)))
	    {
	        typedef typename boost::mpl::next<Iterator>::type iter;
	        return exec_if_2dim_impl<boost::is_same<iter, LastIterator>::value>
		        ::execute(static_cast<Sequence*>(0), static_cast<iter*>(0), static_cast<LastIterator*>(0), p1, p2, e);
	    }
	    else
	    {
	        typedef typename boost::mpl::begin<Sequence>::type first;
	        typedef typename boost::mpl::end<Sequence>::type last;

	        return exec_if_1dim_impl<boost::is_same<first,last>::value>
	            ::execute(static_cast<T1*>(0), static_cast<first*>(0), static_cast<last*>(0), p2, e);
	    }
    }
};

template< class Sequence, class Pred1, class Pred2, class Exec >
inline typename Exec::result_type exec_if_2dim( const Pred1& p1, const Pred2& p2, const Exec& e, Sequence* = 0 )
{
    BOOST_MPL_ASSERT(( boost::mpl::is_sequence<Sequence> ));

    typedef typename boost::mpl::begin<Sequence>::type first;
    typedef typename boost::mpl::end<Sequence>::type last;

    return exec_if_2dim_impl<boost::is_same<first,last>::value>
        ::execute(static_cast<Sequence*>(0), static_cast<first*>(0), static_cast<last*>(0), p1, p2, e);
}

} // namespace BlasBooster

#endif /* EXEC_IF_2DIM_H_ */
