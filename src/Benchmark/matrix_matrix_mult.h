#pragma once

#include <string>
#include <tuple>

#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/Threshold.h"
#include "BrainTwister/benchmark.h"

namespace BlasBooster {

std::tuple<Matrix<Dense,double>, size_t, std::string>
matrix_matrix_mult(std::string const& action, BrainTwister::Benchmark const& benchmark, Threshold const& threshold,
    Matrix<Dense,double> const& refA, Matrix<Dense,double> const& refB);

} // namespace BlasBooster
