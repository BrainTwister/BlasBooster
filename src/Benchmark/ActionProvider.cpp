#include "ActionProvider.h"
#include "ActionOpenBlasDgemm.h"

namespace BlasBooster {

ActionProvider::ActionProvider(ptree const& tree)
{
    for (auto&& leaf : tree) {
    	if (leaf.first == "openblas_dgemm") {
    		action_list.push_back(std::make_shared<ActionOpenBlasDgemm>(leaf.second));
    	} else if (leaf.first == "openblas_sgemm") {

    	} else {
            std::runtime_error(std::string("Unknown action: ") + leaf.first);
        }
    }
}

} // namespace BlasBooster
