#pragma once

#include <iostream>
#include <string>
#include <tuple>

#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/Threshold.h"
#include "BrainTwister/benchmark.h"

namespace BlasBooster {

typedef std::vector<std::tuple<std::string, BrainTwister::myclock::duration>> Details;

std::ostream& operator << (std::ostream& os, BrainTwister::myclock::duration const& duration);

std::ostream& operator << (std::ostream& os, Details const& details);

std::tuple<Matrix<Dense, double>, BrainTwister::myclock::duration, Details>
matrix_matrix_mult(std::string const& action, BrainTwister::Benchmark const& benchmark,
    Threshold const& threshold, Matrix<Dense,double> const& refA, Matrix<Dense,double> const& refB);

} // namespace BlasBooster
