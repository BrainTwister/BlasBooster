#pragma once

#include "BrainTwister/Record.h"
#include "Matrix.h"
#include "PatternGenerator.h"
#include <fstream>
#include <stdexcept>
#include <string>

namespace BlasBooster {

class Reporter {

public:

    Reporter( BlasFunctionName blasFunction );

    template <class T>
    void registerValue( const T& value ) const;

    template <class T, class P>
    void registerMatrix( const DenseMatrix<T,P>& matrix, const std::string& identifier );

    void registerTime( const std::string& time ) {
        report_ << "Time = " << time << std::endl;
    }

private:

    class Settings {
    public:

        bool calculateNorm;
        bool calculateOccupation;
        bool generatePattern;
        boost::filesystem::path reportDirectory;
        boost::filesystem::path blasCallNumberFile;
        double occupationThreshold;
        PatternGenerator::Settings patternSettings;

    Settings settings;

    size_t call_number;

    BlasFunctionName currentBlasFunction_;

    std::ofstream report_;

}; // class BlasAnalyzer

template <class T>
void ReportManager::registerMatrix(Matrix<Dense, T> const& matrix, std::string const& identifier)
{

    report_ << identifier << endl;
    report_ << std::string(identifier.size(),'-') << endl;
    report_ << "Matrix norm = " << matrix.getNorm() << endl;
    report_ << "Matrix occupation = " << matrix.getOccupation( settings_.occupationThreshold ) << endl;

    if ( settings_.generatePattern ) {
        path matrixDir(settings_.reportDirectory / string("BlasCall"
            + boost::lexical_cast<std::string>(blasCallNumber_)));
        if (!exists(matrixDir)) create_directory(matrixDir);
        path matrixFile(matrixDir / (identifier + ".xpm") );
        PatternGenerator generator(settings_.patternSettings);
        generator.generate(matrix,matrixFile);
        report_ << "Matrix pattern file = " << matrixFile.string() << endl;
    }
    report_ << endl;
}

} // namespace BlasBooster
