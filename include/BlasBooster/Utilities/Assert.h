#include <boost/mpl/assert.hpp>
#include <stdexcept>

#ifndef ASSERT_H_
#define ASSERT_H_

#define BLASBOOSTER_TEST_STATIC_ASSERT

#ifdef BLASBOOSTER_TEST_STATIC_ASSERT
    #define STATIC_ASSERT(pred) \
        if ( sizeof(pred) == 0 ) throw std::runtime_error("STATIC_ASSERT");
#else
    #define STATIC_ASSERT(pred) BOOST_MPL_ASSERT(pred)
#endif

#endif /* ASSERT_H_ */
