#ifndef PEAKMANAGER_H
#define PEAKMANAGER_H
#include "peak.h"
#include <vector>

class PeakManager
{
public:
    PeakManager();

    Peak* targetedpeak;
    Peak* previouspeak;
    std::vector<Peak*> peaklist;
    std::vector<double>* x;
    std::vector<double>* y;


    bool allpeaksfound;

    void setEventstarttime(double eventstarttime_);
    void setEventendtime(double eventendtime_);
    double getEventstarttime();
    double getEventendtime();

    void erasePeaks();
    void setTargetedpeak();
    void setPreviouspeak();
    void findAllpeaks();
    void findPeak();
    void findMaximum();
    void findMinimum();

private:
    double eventstarttime;
    double eventendtime;

};

#endif // PEAKMANAGER_H
