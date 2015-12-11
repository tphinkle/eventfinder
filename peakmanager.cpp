#include "peakmanager.h"

PeakManager::PeakManager()
{

    allpeaksfound = false;

}

void PeakManager::erasePeaks()
{
    if(peaklist.size() > 0)
    {
        peaklist.resize(0);
    }

    return;
}

void PeakManager::setTargetedpeak()
{
    return;
}

void PeakManager::setPreviouspeak()
{

    return;
}

double PeakManager::getEventstarttime()
{
    return eventstarttime;
}

void PeakManager::setEventstarttime(double eventstarttime_)
{
    eventstarttime = eventstarttime_;
    return;
}

double PeakManager::getEventendtime()
{
    return eventendtime;
}


void PeakManager::setEventendtime(double eventendtime_)
{
    eventendtime = eventendtime_;
    return;
}

void PeakManager::findAllpeaks()
{



    return;
}

void PeakManager::findPeak()
{

    return;
}

void PeakManager::findMaximum()
{

    return;
}

void PeakManager::findMinimum()
{
    return;
}

