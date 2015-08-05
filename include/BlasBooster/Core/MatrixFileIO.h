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
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include <fstream>

namespace BlasBooster {

template <class M, class T, class P>
struct MatrixFileReader
{
    void operator () (filesystem::path const& file) const
    {
        static_assert(wrong_t<M>::value, "Primary template must not be instantiated.");
    }
};

template <class T, class P>
struct MatrixFileReader<Dense,T,P>
{
    void operator () (filesystem::path const& file) const
    {

    }
};

} // namespace BlasBooster

#endif /* BLASBOOSTER_CORE_MATRIXFILEIO_H_ */
