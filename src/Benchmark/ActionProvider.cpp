#include "ActionProvider.h"
#ifdef WITH_OPENBLAS
    #include "Action_openblas_dgemm.h"
    #include "Action_openblas_sgemm.h"
#endif
#ifdef WITH_INTELMKL
    #include "Action_intelmkl_dgemm.h"
    #include "Action_intelmkl_sgemm.h"
    //#include "Action_intelmkl_dcsrmm.h"
    //#include "Action_intelmkl_scsrmm.h"
    //#include "Action_intelmkl_dcsrmultcsr.h"
    //#include "Action_intelmkl_scsrmultcsr.h"
#endif
#ifdef WITH_EIGEN
    #include "Action_eigen_dgemm.h"
    #include "Action_eigen_sgemm.h"
//    #include "Action_eigen_sdgemm.h"
//    #include "Action_eigen_dsgemm.h"
#endif
#include "Action_blasbooster_block.h"
//#include "Action_blasbooster_sparse_double.h"
//#include "Action_blasbooster_sparse_float.h"
#include "Action_native_dense.h"

namespace BlasBooster {

ActionProvider::ActionProvider(ptree const& tree)
{
    for (auto&& leaf : tree) {
#ifdef WITH_OPENBLAS
    	if (leaf.first == "openblas_dgemm") {
    		action_list.push_back(std::make_shared<Action_openblas_dgemm>(leaf.second));
    	} else
    	if (leaf.first == "openblas_sgemm") {
    		action_list.push_back(std::make_shared<Action_openblas_sgemm>(leaf.second));
    	} else
#endif
#ifdef WITH_INTELMKL
        if (leaf.first == "intelmkl_dgemm") {
    		action_list.push_back(std::make_shared<Action_intelmkl_dgemm>(leaf.second));
    	} else
    	if (leaf.first == "intelmkl_sgemm") {
    		action_list.push_back(std::make_shared<Action_intelmkl_sgemm>(leaf.second));
//    	} else
//    	if (leaf.first == "intelmkl_dcsrmm") {
//    		action_list.push_back(std::make_shared<Action_intelmkl_dcsrmm>(leaf.second));
//    	} else
//    	if (leaf.first == "intelmkl_scsrmm") {
//    		action_list.push_back(std::make_shared<Action_intelmkl_scsrmm>(leaf.second));
//    	} else
//    	if (leaf.first == "intelmkl_dcsrmultcsr") {
//    		action_list.push_back(std::make_shared<Action_intelmkl_dcsrmultcsr>(leaf.second));
//    	} else
//    	if (leaf.first == "intelmkl_scsrmultcsr") {
//    		action_list.push_back(std::make_shared<Action_intelmkl_scsrmultcsr>(leaf.second));
    	} else
#endif
#ifdef WITH_EIGEN
    	if (leaf.first == "eigen_dgemm") {
    		action_list.push_back(std::make_shared<Action_eigen_dgemm>(leaf.second));
    	} else
    	if (leaf.first == "eigen_sgemm") {
    		action_list.push_back(std::make_shared<Action_eigen_sgemm>(leaf.second));
    	} else
//		if (leaf.first == "eigen_sdgemm") {
//			action_list.push_back(std::make_shared<Action_eigen_sdgemm>(leaf.second));
//		} else
//		if (leaf.first == "eigen_dsgemm") {
//			action_list.push_back(std::make_shared<Action_eigen_dsgemm>(leaf.second));
//		} else
#endif
        if (leaf.first == "blasbooster_block") {
    		action_list.push_back(std::make_shared<Action_blasbooster_block>(leaf.second));
      	} else
    	if (leaf.first == "native_dense") {
    		action_list.push_back(std::make_shared<Action_native_dense>(leaf.second));
//    	} else
//    	if (leaf.first == "blasbooster_sparse_double") {
//    		action_list.push_back(std::make_shared<Action_blasbooster_sparse_double>(leaf.second));
//    	} else
//    	if (leaf.first == "blasbooster_sparse_float") {
//    		action_list.push_back(std::make_shared<Action_blasbooster_sparse_float>(leaf.second));
    	} else {
            std::runtime_error(std::string("Unknown action: ") + leaf.first);
        }
    }
}

} // namespace BlasBooster
