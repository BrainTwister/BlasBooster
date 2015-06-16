#ifndef SCOPEDTIMER_H_
#define SCOPEDTIMER_H_

#include <chrono>
#include <string>

class ScopedTimer
{
public:

    ScopedTimer(std::string const& label)
     : label(label),
       start(std::chrono::high_resolution_clock::now())
    {}

    virtual ~ScopedTimer()
    {
        std::chrono::duration<double> elapsed_seconds = std::chrono::high_resolution_clock::now() - start;
        std::cout << "Time of " << label << elapsed_seconds.count() << std::endl;
    }

private:

    std::string label;

    std::chrono::time_point<std::chrono::high_resolution_clock> start;

};

#endif /* SCOPEDTIMER_H_ */
