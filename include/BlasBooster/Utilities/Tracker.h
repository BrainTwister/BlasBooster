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
    Eigen_dgemm,
    Eigen_sgemm,
    Eigen_sdgemm,
    Eigen_dsgemm,
    Blaze_dgemm,
    Blaze_sgemm,
    Blaze_sdgemm,
    Blaze_dsgemm,
	Native_GeneralDense,
	Native_sparse,
	Native_sparse_dense,
	Native_dense_sparse,
	Native_matrix_zero,
	Native_zero_matrix,
	Native_zero_zero,
	get_detection_arrays,
	get_block_size,
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
        map("Eigen_dgemm", TrackerID::Eigen_dgemm);
        map("Eigen_sgemm", TrackerID::Eigen_sgemm);
        map("Eigen_sdgemm", TrackerID::Eigen_sdgemm);
        map("Eigen_dsgemm", TrackerID::Eigen_dsgemm);
        map("Blaze_dgemm", TrackerID::Blaze_dgemm);
        map("Blaze_sgemm", TrackerID::Blaze_sgemm);
        map("Blaze_sdgemm", TrackerID::Blaze_sdgemm);
        map("Blaze_dsgemm", TrackerID::Blaze_dsgemm);
        map("Native_GeneralDense", TrackerID::Native_GeneralDense);
        map("Native_sparse", TrackerID::Native_sparse);
        map("Native_sparse_dense", TrackerID::Native_sparse_dense);
        map("Native_dense_sparse", TrackerID::Native_dense_sparse);
        map("Native_matrix_zero", TrackerID::Native_matrix_zero);
        map("Native_zero_matrix", TrackerID::Native_zero_matrix);
        map("Native_zero_zero", TrackerID::Native_zero_zero);
        map("get_detection_arrays", TrackerID::get_detection_arrays);
        map("get_block_size", TrackerID::get_block_size);
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
