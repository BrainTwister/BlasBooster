#pragma once

#include <stddef.h>
#include <array>
#include <chrono>
#include <iostream>
#include <iomanip>

#include "EnumParser.h"

namespace BlasBooster {

enum class TrackerID {
    OpenBLAS_dgemm,
    OpenBLAS_sgemm,
    IntelMKL_dgemm,
    IntelMKL_sgemm,
    IntelMKL_dcsrmm,
    IntelMKL_scsrmm,
    IntelMKL_dcsrmultcsr,
    IntelMKL_scsrmultcsr,
	Native_GeneralDense,
	Native_sparse,
	Native_sparse_dense,
    size
};

#ifdef BLASBOOSTER_USE_TRACKER
    using clock = std::chrono::high_resolution_clock;

    template <>
    inline EnumParser<TrackerID>::EnumParser()
    {
        map("OpenBLAS_dgemm", TrackerID::OpenBLAS_dgemm);
        map("OpenBLAS_sgemm", TrackerID::OpenBLAS_sgemm);
        map("IntelMKL_dgemm", TrackerID::IntelMKL_dgemm);
        map("IntelMKL_sgemm", TrackerID::IntelMKL_sgemm);
        map("IntelMKL_dcsrmm", TrackerID::IntelMKL_dcsrmm);
        map("IntelMKL_scsrmm", TrackerID::IntelMKL_scsrmm);
        map("IntelMKL_dcsrmultcsr", TrackerID::IntelMKL_dcsrmultcsr);
        map("IntelMKL_scsrmultcsr", TrackerID::IntelMKL_scsrmultcsr);
        map("Native_GeneralDense", TrackerID::Native_GeneralDense);
        map("Native_sparse", TrackerID::Native_sparse);
        map("Native_sparse_dense", TrackerID::Native_sparse_dense);
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
            os << "\n"
               << std::setw(20) << "tracker"
               << std::setw(10) << "count"
               << "time\n"
               << std::string(60,'-')
               << std::endl;

            for (size_t i = 0; i != static_cast<size_t>(TrackerID::size); ++i) {
                if (count[i] == 0) continue;
                os << std::setw(20) << EnumParser<TrackerID>()(static_cast<TrackerID>(i))
                   << std::setw(10) << count[i]
                   << time[i].count() << " ns"
                   << std::endl;
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
