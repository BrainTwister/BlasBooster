#ifndef EXEC_IF_H_
#define EXEC_IF_H_

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
struct exec_if_impl
{
    template< class Iterator, class LastIterator, class Pred, class Exec >
    static typename Exec::result_type execute( Iterator*, LastIterator*, const Pred&, const Exec& )
    {
    	throw std::runtime_error("exec_if: type not found.");
    }
};

template<>
struct exec_if_impl<false>
{
    template< class Iterator, class LastIterator, class Pred, class Exec >
    static typename Exec::result_type execute( Iterator*, LastIterator*, const Pred& f, const Exec& e )
    {
	    typedef typename boost::mpl::deref<Iterator>::type item;

	    if (!f(static_cast<item*>(0)))
	    {
	        typedef typename boost::mpl::next<Iterator>::type iter;
	        return exec_if_impl<boost::is_same<iter, LastIterator>::value>
		        ::execute(static_cast<iter*>(0), static_cast<LastIterator*>(0), f, e);
	    }
	    else
	        return e(static_cast<item*>(0));
    }
};

template< class Sequence, class Pred, class Exec >
inline typename Exec::result_type exec_if( const Pred& f, const Exec& e, Sequence* = 0 )
{
    BOOST_MPL_ASSERT(( boost::mpl::is_sequence<Sequence> ));

    typedef typename boost::mpl::begin<Sequence>::type first;
    typedef typename boost::mpl::end<Sequence>::type last;

    return exec_if_impl<boost::is_same<first,last>::value>
        ::execute(static_cast<first*>(0), static_cast<last*>(0), f, e);
}

} // namespace BlasBooster

#endif /* EXEC_IF_H_ */
