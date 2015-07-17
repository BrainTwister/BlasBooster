#ifndef SCOPEDTIMER_H_
#define SCOPEDTIMER_H_

#include <chrono>
#include <string>

class ScopedTimer
{
	using clock = std::chrono::high_resolution_clock;

public:

    ScopedTimer(std::string const& label)
     : label(label),
       start(clock::now())
    {}

    virtual ~ScopedTimer()
    {
        std::chrono::duration<double> elapsed_seconds = clock::now() - start;
        std::cout << std::fixed << std::setprecision(2)
                  << label << ": " << elapsed_seconds.count() << " s" << std::endl;
    }

private:

    std::string label;

    std::chrono::time_point<clock> start;

};

#endif /* SCOPEDTIMER_H_ */
