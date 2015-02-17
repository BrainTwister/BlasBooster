#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <boost/rational.hpp>
#include <boost/type_traits.hpp>

namespace BlasBooster {

inline double& operator += ( double& v1, const boost::rational<int>& v2 ) {
	return v1 += static_cast<double>(v2.numerator()) / v2.denominator();
}

} // namespace BlasBooster

namespace boost {

    template <>
    struct is_arithmetic<boost::rational<int> > : public true_type {};

} // namespace boost

#endif /* RATIONAL_H_ */
