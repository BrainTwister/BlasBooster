#include "time.h"

namespace BlasBooster {

std::ostream& operator << (std::ostream& os, duration_accuracy const& duration_accuracy)
{
    duration_accuracy::set(os, duration_accuracy.digits);
    return os;
}

std::ostream& operator << (std::ostream& os, BrainTwister::myclock::duration const& duration)
{
    auto&& f = os.flags();
    os << std::fixed
              << std::setprecision(duration_accuracy::get(os))
              << 1.0e-9 * std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    os.flags(f);
    return os;
}

} // namespace BlasBooster
