#pragma once

#include <chrono>
#include <string>

namespace BlasBooster {

#ifdef BLASBOOSTER_USE_TRACKER
    struct Tracker
	{
    	using clock = std::chrono::high_resolution_clock;

    	Tracker(std::string const& tag)
    	 : tag(tag), start(clock::now())
    	{}

        virtual ~Tracker()
        {
            auto&& time = clock::now() - start;
            tracker_register.add(tag, time);
        }

        std::chrono::time_point<clock> start;

        std::string tag;
    };
#else
    struct Tracker
    {
    	Tracker(std::string const&) {}
    };
#endif

} // namespace BlasBooster
