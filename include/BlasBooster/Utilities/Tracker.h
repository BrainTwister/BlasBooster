#pragma once

#include <stddef.h>
#include <array>
#include <chrono>
#include <iostream>

#include "EnumParser.h"

namespace BlasBooster {

enum class TrackerID { OpenBLAS_dgemm, OpenBLAS_sgemm, size };

#ifdef BLASBOOSTER_USE_TRACKER
    using clock = std::chrono::high_resolution_clock;

	template <>
	inline EnumParser<TrackerID>::EnumParser()
	{
		map("OpenBLAS_dgemm", TrackerID::OpenBLAS_dgemm);
		map("OpenBLAS_sgemm", TrackerID::OpenBLAS_sgemm);
	}

	struct TrackerRegister
	{
		static void add(TrackerID id, clock::duration const& duration)
		{
			time[static_cast<size_t>(id)] += duration;
			++count[static_cast<size_t>(id)];
		}

		static std::ostream& print(std::ostream& os)
		{
			os <<  "\nTracker information\n------------------\n";
			for (size_t i = 0; i != static_cast<size_t>(TrackerID::size); ++i) {
				os << EnumParser<TrackerID>()(static_cast<TrackerID>(i)) << " " << count[i] << " " << time[i].count() << " ns\n";
			}
			return os;
		}

		static std::array<clock::duration, static_cast<size_t>(TrackerID::size)> time;
		static std::array<size_t, static_cast<size_t>(TrackerID::size)> count;
	};

    template <TrackerID ID>
    struct Tracker
    {
        Tracker() : start(clock::now()) {}

        virtual ~Tracker()
        {
            auto&& time = clock::now() - start;
            TrackerRegister::add(ID, time);
        }

        std::chrono::time_point<clock> start;
    };
#else
    template <TrackerID ID>
    struct Tracker {};
#endif

} // namespace BlasBooster
