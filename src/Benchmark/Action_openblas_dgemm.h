#pragma once

#include "ActionBase.h"
#include "BlasBooster/Core/MatrixMultExp.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"

namespace BlasBooster {

struct Action_openblas_dgemm : public ActionBase
{
    BRAINTWISTER_RECORD( Settings, \
        (( int, number_of_threads, 1 )) \
    );

    Action_openblas_dgemm(ptree const& tree)
     : settings(tree)
    {}

    std::string name() const { return "openblas_dgemm"; }

    ActionBase::ReturnType execute(
        Matrix<Dense,double> const& refA,
        Matrix<Dense,double> const& refB,
        BrainTwister::Benchmark const& benchmark) const
    {
        OpenBLAS_set_num_threads(settings.number_of_threads);

        Matrix<Dense, double> C;
        auto result = benchmark.benchIt([&](){
            C = (refA * refB).template execute<OpenBLAS>();
        });

        Details details;
        return std::make_tuple(C, result.average_time, details);
    }

    Settings settings;
};

} // namespace BlasBooster
