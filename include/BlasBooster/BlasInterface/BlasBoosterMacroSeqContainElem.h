#ifndef BLASBOOSTER_MACRO_SEQ_CONTAIN_ELEM_H_
#define BLASBOOSTER_MACRO_SEQ_CONTAIN_ELEM_H_

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>

// DONT WORK YET

//#define BLASBOOSTER_MACRO_OR(s,state,x)\
//	BOOST_PP_OR(state,x)
//
//#define BLASBOOSTER_MACRO_COMPARE(r,data,elem)\
//	BOOST_PP_EQUAL(data,elem) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))
//
//#define BLASBOOSTER_MACRO_SEQ_CONTAIN_ELEM(seq,elem)\
//    BOOST_PP_SEQ_FOLD_LEFT(BLASBOOSTER_MACRO_OR, 0, BOOST_PP_TUPLE_TO_SEQ(BOOST_PP_SEQ_SIZE(seq),(\
//    	BOOST_PP_SEQ_FOR_EACH(BLASBOOSTER_MACRO_COMPARE,elem,seq)\
//    )))

#endif /* BLASBOOSTER_MACRO_SEQ_CONTAIN_ELEM_H_ */
