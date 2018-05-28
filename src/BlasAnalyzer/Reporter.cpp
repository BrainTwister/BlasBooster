#include "EnvironmentVariables.h"
#include "FileIO.h"
#include "ReportManager.h"

using std::cout;
using std::endl;
using boost::filesystem::path;

namespace BlasBooster {

ReportManager::ReportManager( BlasFunctionName blasFunction )
 : settings_(), blasCallNumber_(0), currentBlasFunction_(blasFunction), report_()
{
    std::string settingsFileString( getEnvVar("BLASANALYZER_SETTINGS") );
    if (settingsFileString.empty()) throw std::runtime_error("BLASANALYZER_SETTINGS not defined");
    path settingsFile(settingsFileString);
    if (!exists(settingsFile)) throw std::runtime_error(settingsFile.string() + " not exist");

    //writeXML(settings_,"BlasAnalyzerSettings","/home/bernd/scratch/settings.xml");
    readXML(settings_,"BlasAnalyzerSettings",settingsFile);

    path reportFile(settings_.reportDirectory/"Report.txt");
    report_.open( reportFile.string().c_str(), std::fstream::app );

    if ( exists(settings_.blasCallNumberFile) )
        readXML(blasCallNumber_,"BlasCallNumber",settings_.blasCallNumberFile);

    report_ << "BLAS call number " << boost::lexical_cast<std::string>(blasCallNumber_ + 1)
            << "(" << currentBlasFunction_ << ")" << endl;
}

ReportManager::~ReportManager() {
    writeXML(++blasCallNumber_,"BlasCallNumber",settings_.blasCallNumberFile);
}

} // namespace BlasBooster
