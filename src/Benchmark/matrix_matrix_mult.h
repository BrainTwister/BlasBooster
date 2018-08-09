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

struct duration_accuracy
{
	duration_accuracy(int digits) : digits(digits) {}

    static void set(std::ios_base& s, int digits)
    {
    	flag(s) = digits;
    }

    static int get(std::ios_base& s)
    {
    	return flag(s);
    }

    int digits;

private:

    static long& flag(std::ios_base& s) {
        static int n = std::ios_base::xalloc();
        return s.iword(n);
    }
};

inline duration_accuracy
set_duration_accuracy(int digits)
{ return {digits}; }

std::ostream& operator << (std::ostream& os, duration_accuracy const& duration_accuracy);

std::ostream& operator << (std::ostream& os, Details const& details);

std::ostream& operator << (std::ostream& os, BrainTwister::myclock::duration const& duration);

std::tuple<Matrix<Dense, double>, BrainTwister::myclock::duration, Details>
matrix_matrix_mult(std::string const& action, BrainTwister::Benchmark const& benchmark,
    Threshold const& threshold, Matrix<Dense,double> const& refA, Matrix<Dense,double> const& refB);

} // namespace BlasBooster
