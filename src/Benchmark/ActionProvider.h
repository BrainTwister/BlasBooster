#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>

#include "ActionBase.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BrainTwister/Record.h"

using boost::property_tree::ptree;

namespace BlasBooster {

class ActionProvider
{
public:

    typedef std::vector<std::shared_ptr<ActionBase>> ActionList;
    typedef bool is_record;

    ActionProvider(ptree const& tree = ptree());

    bool operator == (ActionProvider const& other) const { return action_list == other.action_list; }

    ActionList get() const { return action_list; }

private:

    ActionList action_list;

};

} // namespace BlasBooster
