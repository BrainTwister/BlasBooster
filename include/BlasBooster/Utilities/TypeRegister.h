#ifndef TYPEREGISTER_H_
#define TYPEREGISTER_H_

#include <boost/mpl/distance.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>

template < class TypeList >
struct TypeRegister
{
    template < class T >
    struct getTypeIndex
    {
        typedef typename boost::mpl::begin<TypeList>::type iterBegin;
        typedef typename boost::mpl::end<TypeList>::type iterEnd;
        typedef typename boost::mpl::find<TypeList,T>::type iterFind;
        typedef typename boost::mpl::if_<
            boost::is_same<iterFind,iterEnd>,
            boost::mpl::long_<-1>,
            typename boost::mpl::distance<iterBegin,iterFind>::type
        >::type type;
        static const long value = type::value;
    };

    template < long index >
    struct getType {
        typedef typename boost::mpl::at<TypeList,boost::mpl::long_<index> >::type type;
    };

};

#endif /* TYPEREGISTER_H_ */
