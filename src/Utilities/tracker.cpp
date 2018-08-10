#include "BlasBooster/Utilities/Tracker.h"

using namespace BlasBooster;

#ifdef BLASBOOSTER_USE_TRACKER
    std::array<clock::duration, static_cast<size_t>(TrackerID::size)> TrackerRegister::time;
    std::array<size_t, static_cast<size_t>(TrackerID::size)> TrackerRegister::count;
#endif
