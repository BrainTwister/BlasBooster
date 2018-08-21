#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "time.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BrainTwister/benchmark.h"

namespace BlasBooster {

struct ActionBase
{
	typedef std::vector<std::tuple<std::string, BrainTwister::myclock::duration>> Details;
	typedef std::tuple<Matrix<Dense, double>, BrainTwister::myclock::duration, Details> ReturnType;

	virtual ~ActionBase() {};

	virtual std::string name() const = 0;

    virtual ReturnType execution(
    	Matrix<Dense,double> const& refA,
        Matrix<Dense,double> const& refB,
        BrainTwister::Benchmark const& benchmark) const = 0;
};

inline std::ostream& operator << (std::ostream& os, ActionBase::Details const& details)
{
    for (auto&& [name, time] : details) os << name << ": " << time << " s ";
    return os;
}

} // namespace BlasBooster
