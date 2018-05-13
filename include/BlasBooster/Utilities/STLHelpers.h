#pragma once

#include <iostream>
#include <vector>

namespace BlasBooster {

template < class T >
std::ostream& operator << ( std::ostream& stream, const std::vector<T>& c ) {
    stream << "size = " << c.size() << std::endl;
    for ( typename std::vector<T>::const_iterator iterCur(c.begin()), iterEnd(c.end()); iterCur != iterEnd; ++iterCur ) {
        stream << *iterCur << std::endl;
    }
    return stream;
}

} // namespace BlasBooster
