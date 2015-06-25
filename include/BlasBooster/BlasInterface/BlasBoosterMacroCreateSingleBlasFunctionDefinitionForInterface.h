#ifndef BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DEFINITION_FOR_INTERFACE_H_
#define BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DEFINITION_FOR_INTERFACE_H_

#include "BlasBoosterMacroCreateBlasArgumentListWithNames.h"
#include "BlasBoosterMacroCreateBlasVariableList.h"
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DEFINITION_FOR_INTERFACE(r,data,elem)\
    BOOST_PP_TUPLE_ELEM(3,0,elem) BlasInterface < data, BOOST_PP_TUPLE_ELEM(3,1,elem) >::operator() (BOOST_PP_SEQ_FOR_EACH_I(\
    		BLASBOOSTER_MACRO_CREATE_BLAS_ARGUMENT_LIST_WITH_NAMES,BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3,2,elem)),BOOST_PP_TUPLE_ELEM(3,2,elem))\
    ) {\
	    return :: BOOST_PP_TUPLE_ELEM(3,1,elem) (BOOST_PP_SEQ_FOR_EACH_I(\
            BLASBOOSTER_MACRO_CREATE_BLAS_VARIABLE_LIST,BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3,2,elem)),BOOST_PP_TUPLE_ELEM(3,2,elem)));\
    }

#endif /* BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DEFINITION_FOR_INTERFACE_H_ */
