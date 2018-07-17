#pragma once

#include "BlasBooster/Core/DenseMatrix.h"
#include <boost/property_tree/ptree.hpp>
#include "BrainTwister/Record.h"

namespace BlasBooster {

struct MatrixProvider
{
	typedef bool is_record;

    MatrixProvider(boost::property_tree::ptree const& pt);

    Matrix<Dense, double> get(std::string const& name) const;
};

} // namespace BlasBooster
