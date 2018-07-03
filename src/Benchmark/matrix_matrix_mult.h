#pragma once

#include "BlasBooster/Core/DenseMatrix.h"
#include "BrainTwister/benchmark.h"
#include <string>

namespace BlasBooster {

std::tuple<BrainTwister::Benchmark::Results, Matrix<Dense,double>>
matrix_matrix_mult(std::string const& action, BrainTwister::Benchmark const& benchmark, Threshold const& threshold,
    Matrix<Dense,double> const& refA, Matrix<Dense,double> const& refB);

} // namespace BlasBooster
