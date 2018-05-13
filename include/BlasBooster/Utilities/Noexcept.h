#pragma once

namespace BlasBooster {

#ifdef BLASBOOSTER_USE_NOEXCEPT
    #define BLASBOOSTER_NOEXCEPT noexcept
#else
    #define BLASBOOSTER_NOEXCEPT
#endif

} // namespace BlasBooster
