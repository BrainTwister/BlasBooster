#pragma once

#include <cassert>
#include <map>
#include <string>

namespace BlasBooster {

/**
 * Mapping string to enum and reverse.
 * The enums are always case sensitive, whereas the correlated strings can be handled both,
 * depending on the template argument CS, which is by default true.
 */
//template <class T, bool CS = true>
template <class T>
class EnumParser
{
    typedef std::map<std::string, T> MapStringToEnum;
    typedef std::map<T, std::string> MapEnumToString;

public:

    EnumParser() {}

    T operator () (std::string const& value) const
    {
        typename MapStringToEnum::const_iterator iValue = mapStringToEnum.find(value);
        assert(iValue != mapStringToEnum.end());
        return iValue->second;
    }

    std::string operator () (T value) const
    {
        typename MapEnumToString::const_iterator iValue = mapEnumToString.find(value);
        assert(iValue != mapEnumToString.end());
        return iValue->second;
    }

private:

    void map(std::string const& s, T e)
    {
    	mapStringToEnum[s] = e;
    	mapEnumToString[e] = s;
    }

    MapStringToEnum mapStringToEnum;
    MapEnumToString mapEnumToString;

};

//template <class T>
//T EnumParser<T, false>::operator () (std::string const& value) const
//{
//    typename MapStringToEnum::const_iterator iValue = mapStringToEnum.find(value);
//    if (iValue == mapStringToEnum.end()) gmx_fatal(FARGS, "EnumParser: enum type not found.");
//    return iValue->second;
//}

} // namespace BlasBooster
