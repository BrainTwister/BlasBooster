#ifndef TYPENAME_H_
#define TYPENAME_H_

#include "wrong_t.h"
#include <string>

namespace BlasBooster {

template <class T>
struct TypeName
{
    static_assert(wrong_t<T>::value, "TypeName not found.");
};

template <>
struct TypeName<double>
{
    static const std::string value() { return "double"; }
};

template <>
struct TypeName<float>
{
    static const std::string value() { return "float"; }
};

template <>
struct TypeName<size_t>
{
    static const std::string value() { return "size_t"; }
};

template <>
struct TypeName<int>
{
    static const std::string value() { return "int"; }
};

} // namespace BlasBooster

#endif /* TYPENAME_H_ */
