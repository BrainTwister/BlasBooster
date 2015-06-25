#ifndef BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE_H_
#define BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE_H_

#include "BlasBoosterMacroCreateBlasArgumentList.h"
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE(r,data,elem)\
	template < >\
    struct BlasInterface < data, BOOST_PP_TUPLE_ELEM(3,1,elem) > {\
        BOOST_PP_TUPLE_ELEM(3,0,elem) operator () (BOOST_PP_SEQ_FOR_EACH_I(\
    		BLASBOOSTER_MACRO_CREATE_BLAS_ARGUMENT_LIST,BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3,2,elem)),BOOST_PP_TUPLE_ELEM(3,2,elem))\
        );\
    };

#endif /* BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE_H_ */
