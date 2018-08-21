#pragma once

#include <iostream>
#include <string>
#include <tuple>

#include "BrainTwister/benchmark.h"

namespace BlasBooster {

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

inline duration_accuracy set_duration_accuracy(int digits)
{
    return {digits};
}

std::ostream& operator << (std::ostream& os, duration_accuracy const& duration_accuracy);

std::ostream& operator << (std::ostream& os, BrainTwister::myclock::duration const& duration);

} // namespace BlasBooster
