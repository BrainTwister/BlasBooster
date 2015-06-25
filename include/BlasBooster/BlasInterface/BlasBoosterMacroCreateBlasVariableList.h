#ifndef BLASBOOSTER_MACRO_CREATE_BLAS_VARIABLE_LIST_H_
#define BLASBOOSTER_MACRO_CREATE_BLAS_VARIABLE_LIST_H_

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>

#define BLASBOOSTER_MACRO_CREATE_BLAS_VARIABLE_LIST(r,size,i,elem)\
	BOOST_PP_CAT(v,i) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#endif /* BLASBOOSTER_MACRO_CREATE_BLAS_VARIABLE_LIST_H_ */
