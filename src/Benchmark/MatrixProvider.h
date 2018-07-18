#pragma once

#include "BlasBooster/Core/DenseMatrix.h"
#include <boost/property_tree/ptree.hpp>
#include "BrainTwister/Record.h"
#include <string>
#include <unordered_map>
#include <vector>

using boost::property_tree::ptree;

namespace BlasBooster {

class MatrixProvider
{
	typedef std::vector<Matrix<Dense, double>> MatrixList;
	typedef std::unordered_map<std::string, MatrixList> MatrixSet;

public:

	typedef bool is_record;

    MatrixProvider(ptree const& tree = ptree());

    bool operator == (MatrixProvider const& other) const { return matrix_set == other.matrix_set; }

    MatrixList get(std::string const& name) const { return matrix_set.find(name)->second; }

private:

    MatrixSet matrix_set;

};

} // namespace BlasBooster
