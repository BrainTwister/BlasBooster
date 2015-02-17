#ifndef EQUALWITHINNUMERICALACCURACY_H_
#define EQUALWITHINNUMERICALACCURACY_H_

#include <algorithm>
#include <complex>

namespace BlasBooster {

template < class T > double numericalAccuracy();

template <> inline double numericalAccuracy< double >() {	return 1e-12; }
template <> inline double numericalAccuracy< std::complex<double> >() { return 1e-12; }
template <> inline double numericalAccuracy< float >() { return 1e-4; }
template <> inline double numericalAccuracy< int >() { return 0.0; }
template <> inline double numericalAccuracy< unsigned int >() { return 0.0; }
template <> inline double numericalAccuracy< unsigned long >() { return 0.0; }

template <class T1, class T2>
bool equalWithinNumericalAccuracy(T1 const& v1, T2 const& v2)
{
	return std::abs(v1 - v2) <= std::max(numericalAccuracy<T1>(),numericalAccuracy<T2>());
}

} // namespace BlasBooster

#endif /* EQUALWITHINNUMERICALACCURACY_H_ */
