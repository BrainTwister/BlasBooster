#ifndef NOEXCEPT_H_
#define NOEXCEPT_H_

namespace BlasBooster {

#ifdef BLASBOOSTER_USE_NOEXCEPT
    #define BLASBOOSTER_NOEXCEPT noexcept
#else
    #define BLASBOOSTER_NOEXCEPT
#endif

} // namespace BlasBooster

#endif /* NOEXCEPT_H_ */
