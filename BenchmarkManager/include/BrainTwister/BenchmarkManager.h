#ifndef BRAINTWISTER_BENCHMARKMANAGER_H_
#define BRAINTWISTER_BENCHMARKMANAGER_H_

#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <set>

namespace BrainTwister {

template <class Rep, class Period,
          class = typename std::enable_if
          <
              std::chrono::duration<Rep, Period>::min() <
              std::chrono::duration<Rep, Period>::zero()
          >::type
         >
constexpr
inline
std::chrono::duration<Rep, Period>
abs(std::chrono::duration<Rep, Period> d)
{
    return d >= d.zero() ? d : -d;
}

/**
 * Accurate time measurement by repeated execution
 */
class BenchmarkManager
{

    /// Take the clock with the highest precision
    using clock = std::chrono::high_resolution_clock;

public:

    /**
     * For accurate timings a minimum execution time is needed. Therefore for fast routines
     * the execution will be repeated until minExecutionTime is reached. The total time
     * will be divided by the number of cycles. If execution time is larger than minExecutionTime
     * the execution will repeated at least as minNbOfReplications. minNbOfReplications should
     * not smaller than 3 to detect spikes.
     * Spikes are measurements outside the meanValue +/- spikeDetectionValue * meanValue.
     */
    struct Settings
    {
    	Settings(size_t minReplications = 3,
    			 clock::duration minExecutionTime = std::chrono::seconds(1),
				 double spikeDetection = 0.1)
    	 : minReplications(minReplications),
		   minExecutionTime(minExecutionTime),
		   spikeDetection(spikeDetection)
    	{};

        size_t minReplications;
        clock::duration minExecutionTime;
        double spikeDetection;
    };

    struct Result
    {
    	clock::duration averageTime;
    	clock::duration shortestTime;
    	clock::duration longestTime;
	    size_t nbReplications = 0;
	    size_t num_spikes = 0;
	    double mflops;
    };

    BenchmarkManager(Settings const& settings = Settings())
     : settings(settings)
    {}

    /// Calling a benchmark for a given action
    template <class Action>
    Result benchIt(Action const& action) const
    {
        // Prepare action
        action.initialize();

        Result result;
        clock::duration total_time(0);
        std::set<clock::duration> times;
        while (total_time < settings.minExecutionTime or result.nbReplications < settings.minReplications)
        {
            auto time = measure_time(action);
            times.insert(time);
            total_time += time;
            ++result.nbReplications;
        }

        // Remeasure spikes
        while (*times.rbegin() > *times.begin() * (settings.spikeDetection + 1))
        {
            auto time = measure_time(action);
            times.insert(time);
            ++result.num_spikes;
            total_time += time; 
            total_time -= *times.rbegin(); 
            times.erase(std::prev(times.end()));
        }

        result.nbReplications = times.size();
        result.averageTime = total_time / result.nbReplications;
        result.shortestTime = *times.begin();
        result.longestTime = *times.rbegin();

        // Check result
        action.check();

        return result;
    }

private:

    /// Determine a single execution time
    template <class Action>
    clock::duration measure_time(Action const& action) const
    {
        std::chrono::time_point<clock> start = clock::now();
        action.execute();
        return clock::now() - start;
    }

    /// General settings for the benchmark execution
    Settings settings;

};

} // namespace BrainTwister

#endif /* BRAINTWISTER_BENCHMARKMANAGER_H_ */

