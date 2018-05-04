// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_MATRIXFILEIO_H_
#define BLASBOOSTER_CORE_MATRIXFILEIO_H_

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BrainTwister/Record.h"
#include <iostream>
#include <fstream>
// tmp
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace BlasBooster {

BRAINTWISTER_RECORD( MatrixFileSettings,\
	(( size_t, nbRows, 0 ))\
	(( size_t, nbColumns, 0 ))\
	(( size_t, rowLeadingDimension, 0 ))\
	(( size_t, columnLeadingDimension, 0 ))\
	(( size_t, rowOffset, 0 ))\
	(( size_t, columnOffset, 0 ))\
	(( std::string, filename, "" ))\
)

/// Reading dense matrix from stream
template <class T, class P>
std::istream& operator >> (std::istream& is, Matrix<Dense,T,P>& matrix)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(is, tree);
    MatrixFileSettings settings(tree);
	matrix.resize(settings.nbRows, settings.nbColumns);

	// Some dimension checks
	if (settings.nbRows + settings.rowOffset > settings.rowLeadingDimension) throw BlasBoosterException("");
	if (settings.nbColumns + settings.columnOffset > settings.columnLeadingDimension) throw BlasBoosterException("");

	std::ifstream is2(settings.filename, std::ifstream::binary);
	if (!is2) throw BlasBoosterException("Can't open file " + settings.filename);

	T* dataPointer = matrix.getDataPointer();

	if (settings.nbColumns == settings.columnLeadingDimension and settings.nbRows == settings.rowLeadingDimension) {
        is2.read(reinterpret_cast<char*>(dataPointer), settings.nbRows * settings.nbColumns * sizeof(T));
	} else {
		is2.seekg((settings.columnOffset * settings.rowLeadingDimension + settings.rowOffset) * sizeof(T), is.cur);
		for (size_t col = 0; col < settings.nbColumns; ++col) {
			is2.read(reinterpret_cast<char*>(dataPointer), settings.nbRows * sizeof(T));
			dataPointer += settings.nbRows;
			is2.seekg((settings.rowLeadingDimension - settings.nbRows) * sizeof(T), is.cur);
		}
	}

	return is;
}

#if 0
/// Writing dense matrix to stream
template <class T, class P>
std::ostream& operator << (std::ostream& os, Matrix<Dense,T,P> const& matrix)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(is, tree);
    MatrixFileSettings settings(tree);
	matrix.resize(settings.nbRows, settings.nbColumns);

	// Some dimension checks
	if (settings.nbRows + settings.rowOffset > settings.rowLeadingDimension) throw BlasBoosterException("");
	if (settings.nbColumns + settings.columnOffset > settings.columnLeadingDimension) throw BlasBoosterException("");

	std::ifstream is2(settings.filename, std::ifstream::binary);
	if (!is2) throw BlasBoosterException("Can't open file " + settings.filename);

	T* dataPointer = matrix.getDataPointer();

	if (settings.nbColumns == settings.columnLeadingDimension and settings.nbRows == settings.rowLeadingDimension) {
        is2.read(reinterpret_cast<char*>(dataPointer), settings.nbRows * settings.nbColumns * sizeof(T));
	} else {
		is2.seekg((settings.columnOffset * settings.rowLeadingDimension + settings.rowOffset) * sizeof(T), is.cur);
		for (size_t col = 0; col < settings.nbColumns; ++col) {
			is2.read(reinterpret_cast<char*>(dataPointer), settings.nbRows * sizeof(T));
			dataPointer += settings.nbRows;
			is2.seekg((settings.rowLeadingDimension - settings.nbRows) * sizeof(T), is.cur);
		}
	}

	return is;
}
#endif

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_MATRIXFILEIO_H_
