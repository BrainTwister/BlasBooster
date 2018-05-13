#pragma once

#include "BlasBoosterException.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <boost/serialization/nvp.hpp>
#include <fstream>
#include <string>

namespace BlasBooster {

template <class T>
void readXML( T& settings, const std::string& name, const boost::filesystem::path& filename )
{
    if (!exists(filename)) throw BlasBoosterException("readXML: " + filename.string() + " not exist");
    std::ifstream in(filename.string().c_str());
    boost::archive::xml_iarchive ia(in);
    ia >> boost::serialization::make_nvp(name.c_str(),settings);
}

template <class T>
void writeXML( T& settings, const std::string& name, const boost::filesystem::path& filename,
    bool overwrite = true )
{
    if (!overwrite and exists(filename)) throw BlasBoosterException("writeXML: " + filename.string() + " exist");
    std::ofstream out(filename.string().c_str());
    boost::archive::xml_oarchive oa(out);
    oa << boost::serialization::make_nvp(name.c_str(),settings);
}

template <class T>
void readBinary( T& settings, const std::string& name, const boost::filesystem::path& filename )
{
    if (!exists(filename)) throw BlasBoosterException("readBinary: " + filename.string() + " not exist");
    std::ifstream in(filename.string().c_str());
    boost::archive::binary_iarchive ia(in);
    ia >> boost::serialization::make_nvp(name.c_str(),settings);
}

template <class T>
void writeBinary( T& settings, const std::string& name, const boost::filesystem::path& filename,
    bool overwrite = true )
{
    if (!overwrite and exists(filename)) throw BlasBoosterException("writeBinary: " + filename.string() + " exist");
    std::ofstream out(filename.string().c_str());
    boost::archive::binary_oarchive oa(out);
    oa << boost::serialization::make_nvp(name.c_str(),settings);
}

} // namespace BlasBooster
